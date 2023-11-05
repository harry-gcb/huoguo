#ifdef USE_SELECT_POLLER

#include "utils_logger.h"
#include "net_ioevent.h"
#include "net_socket.h"
#include "net_channel.h"
#include "net_poller_select.h"

namespace huoguo {
namespace net {

#define MAX_SOCKET_EVENTS 1024

SelectPoller::SelectPoller() {
}

SelectPoller::~SelectPoller() {
}

int SelectPoller::add_event(std::shared_ptr<EventIO> event, bool enable_read, bool enable_write) {
    m_eventfds.push_front({event->get_fd(), event->get_channel(), enable_read, enable_write});
    DebugL("ADD [%s], ret=%d, fd=%d, read=%d, write=%d", event->get_channel()->get_trace_id().c_str(), m_eventfds.size(), event->get_fd(), enable_read, enable_write);
    return 0;
}

int SelectPoller::set_event(std::shared_ptr<EventIO> event, bool enable_read, bool enable_write) {
    auto it = std::find_if(m_eventfds.begin(), m_eventfds.end(), [event](const EventFd &eventfd) {
        return eventfd.m_fd == event->get_fd();
    });
    if (it == m_eventfds.end()) {
        return -1;
    }
    it->m_user_data = event->get_channel();
    it->m_enable_read = enable_read;
    it->m_enable_write = enable_write;
    DebugL("MOD [%s], ret=%d, fd=%d, read=%d, write=%d",event->get_channel()->get_trace_id().c_str(), m_eventfds.size(), event->get_fd(), enable_read, enable_write);
    return 0;
}

int SelectPoller::del_event(std::shared_ptr<EventIO> event) {
    auto it = std::find_if(m_eventfds.begin(), m_eventfds.end(), [event](const EventFd &eventfd) {
        return eventfd.m_fd == event->get_fd();
    });
    if (it == m_eventfds.end()) {
        return -1;
    }
    DebugL("DEL [%s], ret=%d, fd=%d, read=%d, write=%d",event->get_channel()->get_trace_id().c_str(), m_eventfds.size(), event->get_fd(), it->m_enable_read, it->m_enable_write);
    m_eventfds.erase(it);
    return 0;
}

int SelectPoller::get_event(std::list<std::shared_ptr<IOEvent> >& ioevents, int timeout) {
    fd_set fd_read;
    fd_set fd_write;
    fd_set fd_error;
    FD_ZERO(&fd_read);
    FD_ZERO(&fd_write);
    FD_ZERO(&fd_error);
    for (auto &eventfd: m_eventfds) {
        if (eventfd.m_enable_read) {
            FD_SET(eventfd.m_fd, &fd_read);
        }
        if (eventfd.m_enable_write) {
            FD_SET(eventfd.m_fd, &fd_write);
        }
        if (eventfd.m_enable_write) {
            FD_SET(eventfd.m_fd, &fd_error);
        }
    }
    struct timeval tv = { timeout, 0 };
    int n = select(static_cast<int>(m_eventfds.size()), &fd_read, &fd_write, &fd_error, &tv);
    if (n <= 0) {
        InfoL("select return %n", n);
        return n;
    }
    bool read_occurred = false;
    bool write_occurred = false;
    bool error_occurred = false;
    for (auto &eventfd: m_eventfds) {
        read_occurred = FD_ISSET(eventfd.m_fd, &fd_read);
        write_occurred = FD_ISSET(eventfd.m_fd, &fd_write);
        error_occurred = FD_ISSET(eventfd.m_fd, &fd_error);
        if (!read_occurred && !write_occurred & !error_occurred) {
            continue;
        }
        auto ioevent = std::make_shared<IOEvent>();
        ioevent->m_read_occurred = read_occurred;
        ioevent->m_write_occurred = write_occurred;
        ioevent->m_error_occurred = error_occurred;
        ioevent->m_channel = static_cast<Channel *>(eventfd.m_user_data);
        ioevents.push_back(ioevent);
    }
    return static_cast<int>(ioevents.size());
}

} // namespace net
} // namespace huoguo

#endif