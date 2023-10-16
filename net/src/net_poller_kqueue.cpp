#ifdef USE_KQUEUE_POLLER
#include <unistd.h>
#include <sys/event.h>
#include "net.h"

namespace huoguo {
namespace net {

#define MAX_SOCKET_EVENTS 1024

KQueuePoller::KQueuePoller() {
    m_kqueue_fd = kqueue();
    if (m_kqueue_fd < 0) {
        ERROR("kqueue failed: m_kqueue_fd=%d", m_kqueue_fd);
    }
    DEBUG("KQueuePoller ctor, m_kqueue_fd=%d, this=%p", m_kqueue_fd, this);
}

KQueuePoller::~KQueuePoller() {
    ::close(m_kqueue_fd);
}

int KQueuePoller::add_event(std::shared_ptr<EventIO> event, bool enable_read, bool enable_write) {
    int filter = 0;
    struct kevent ev = { 0 };
    if (1 || enable_read) {
        filter |= EVFILT_READ;
    }
    if (enable_write) {
        filter |= EVFILT_WRITE;
    }
    EV_SET(&ev, event->get_fd(), filter, EV_ADD, 0, 0, event->get_channel());
    int ret = kevent(m_kqueue_fd, &ev, 1, nullptr, 0, nullptr);
    DEBUG("[%s] kevent ADD: ret=%d, errno=%d, socket=%d, read=%d, write=%d", event->get_channel()->get_trace_id().c_str(), ret, errno, event->get_fd(), enable_read, enable_write);
    return ret;
}

int KQueuePoller::set_event(std::shared_ptr<EventIO> event, bool enable_read, bool enable_write) {
    int filter = 0;
    struct kevent ev = { 0 };
    if (enable_read) {
        filter |= EVFILT_READ;
    }
    if (enable_write) {
        filter |= EVFILT_WRITE;
    }
    EV_SET(&ev, event->get_fd(), filter, EV_ENABLE, 0, 0, event->get_channel());
    int ret = kevent(m_kqueue_fd, &ev, 1, nullptr, 0, nullptr);
    DEBUG("[%s] kevent MOD: ret=%d, errno=%d, socket=%d, read=%d, write=%d", event->get_channel()->get_trace_id().c_str(), ret, errno, event->get_fd(), enable_read, enable_write);
    return ret;
}

int KQueuePoller::del_event(std::shared_ptr<EventIO> event) {
    int filter = 0;
    struct kevent ev = { 0 };
    EV_SET(&ev, event->get_fd(), filter, EV_DELETE, 0, 0, event->get_channel());
    int ret = kevent(m_kqueue_fd, &ev, 1, nullptr, 0, nullptr);
    DEBUG("[%s] kevent DEL: ret=%d, errno=%d, socket=%d", event->get_channel()->get_trace_id().c_str(), ret, errno, event->get_fd());
    return ret;
}

int KQueuePoller::get_event(std::list<std::shared_ptr<IOEvent> >& ioevents, int timeout) {
    struct kevent events[MAX_SOCKET_EVENTS] = { 0 };
    struct timespec ts;
    ts.tv_sec = timeout / 1000;
    ts.tv_nsec = (timeout % 1000) * 1000 * 1000;
    int ret = kevent(m_kqueue_fd, nullptr, 0, events, MAX_SOCKET_EVENTS, &ts);
    if (ret < 0) {
        return 0;
    }
    for (int i = 0; i < ret; ++i) {
        auto ioevent = std::make_shared<IOEvent>();
        ioevent->m_channel = static_cast<Channel *>(events[i].udata);
        // ioevent->m_error_occurred = events[i].filter & (EPOLLERR | EPOLLHUP);
        ioevent->m_read_occurred  = events[i].filter & EVFILT_READ;
        ioevent->m_write_occurred = events[i].filter & EVFILT_WRITE;
        ioevents.push_back(ioevent);
    }
    return ret;
}

} // namespace net
} // namespace huoguo
#endif