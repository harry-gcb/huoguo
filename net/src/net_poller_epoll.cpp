#ifdef USE_EPOLL_POLLER
#include <sys/epoll.h>
#include <unistd.h>
#include "utils.h"
#include "net_poller_epoll.h"
#include "net_ioevent.h"
#include "net_socket.h"
#include "net_channel.h"

namespace huoguo {
namespace net {

#define MAX_SOCKET_EVENTS 1024

EPollPoller::EPollPoller() {
    m_epoll_fd = epoll_create(MAX_SOCKET_EVENTS);
    if (m_epoll_fd < 0) {
        ErrorL("epoll_create failed: m_epoll_fd=%d", m_epoll_fd);
    }
}

EPollPoller::~EPollPoller() {
    close(m_epoll_fd);
}

int EPollPoller::add_event(std::shared_ptr<EventIO> event, bool enable_read, bool enable_write) {
    struct epoll_event ev = { 0 };
    ev.data.ptr = event->get_channel();
    ev.events = 0;
    if (enable_read) {
        ev.events |= EPOLLIN;
    }
    if (enable_write) {
        ev.events |= EPOLLOUT;
    }
    int ret = epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, event->get_fd(), &ev);
    DebugL("[%s] epoll_ctl ADD, ret=%d, fd=%d, read=%d, write=%d", event->get_channel()->get_trace_id().c_str(), ret, event->get_fd(), enable_read, enable_write);
    return ret;
}

int EPollPoller::set_event(std::shared_ptr<EventIO> event, bool enable_read, bool enable_write) {
    struct epoll_event ev = { 0 };
    ev.data.ptr = event->get_channel();
    ev.events = 0;
    if (enable_read) {
        ev.events |= EPOLLIN;
    }
    if (enable_write) {
        ev.events |= EPOLLOUT;
    }
    int ret = epoll_ctl(m_epoll_fd, EPOLL_CTL_MOD, event->get_fd(), &ev);
    DebugL("[%s] epoll_ctl MOD, ret=%d, fd=%d, read=%d, write=%d",event->get_channel()->get_trace_id().c_str(), ret, event->get_fd(), enable_read, enable_write);
    return ret;
}

int EPollPoller::del_event(std::shared_ptr<EventIO> event) {
    struct epoll_event ev = { 0 };
    ev.data.ptr = event->get_channel();
    ev.events = 0;
    int ret = epoll_ctl(m_epoll_fd, EPOLL_CTL_DEL, event->get_fd(), &ev);
    DebugL("[%s] epoll_ctl DEL, ret=%d, fd=%d", event->get_channel()->get_trace_id().c_str(), ret, event->get_fd());
    return ret;
}

int EPollPoller::get_event(std::list<std::shared_ptr<IOEvent> >& ioevents, int timeout) {
    struct epoll_event events[MAX_SOCKET_EVENTS] = { 0 };
    int ret = epoll_wait(m_epoll_fd, events, MAX_SOCKET_EVENTS, timeout);
    for (int i = 0; i < ret; ++i) {
        auto ioevent = std::make_shared<IOEvent>();
        ioevent->m_channel = static_cast<Channel *>(events[i].data.ptr);
        ioevent->m_error_occurred = events[i].events & (EPOLLERR | EPOLLHUP);
        ioevent->m_read_occurred  = events[i].events & EPOLLIN;
        ioevent->m_write_occurred = events[i].events & EPOLLOUT;
        ioevents.push_back(ioevent);
    }
    return ret;
}

} // namespace net
} // namespace huoguo
#endif