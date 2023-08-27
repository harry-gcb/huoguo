#ifdef USE_EPOLL
#include <sys/epoll.h>
#include <unistd.h>
#include "epoll_poller.h"
#include "socket.h"
#include "logger.h"

namespace huoguo {
namespace net {

#define MAX_SOCKET_EVENTS 1024

EPollPoller::EPollPoller() {
    m_epoll_fd = epoll_create(MAX_SOCKET_EVENTS);
    if (m_epoll_fd < 0) {
        ERROR("epoll_create failed: m_epoll_fd=%d", m_epoll_fd);
    }
}

EPollPoller::~EPollPoller() {
    close(m_epoll_fd);
}

int EPollPoller::add_event(std::shared_ptr<Socket> sock, bool enable_read, bool enable_write) {
    struct epoll_event ev = { 0 };
    ev.data.ptr = sock->get_channel();
    ev.events = 0;
    if (enable_read) {
        ev.events |= EPOLLIN;
    }
    if (enable_write) {
        ev.events |= EPOLLOUT;
    }
    int ret = epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, sock->get_handle(), &ev);
    INFO("epoll_ctl ADD: ret=%d, socket=%d, read=%d, write=%d", ret, sock->get_handle(), enable_read, enable_write);
    return ret;
}

int EPollPoller::set_event(std::shared_ptr<Socket> sock, bool enable_read, bool enable_write) {
    struct epoll_event ev = { 0 };
    ev.data.ptr = sock->get_channel();
    ev.events = 0;
    if (enable_read) {
        ev.events |= EPOLLIN;
    }
    if (enable_write) {
        ev.events |= EPOLLOUT;
    }
    int ret = epoll_ctl(m_epoll_fd, EPOLL_CTL_MOD, sock->get_handle(), &ev);
    INFO("epoll_ctl MOD: ret=%d, socket=%d, read=%d, write=%d", ret, sock->get_handle(), enable_read, enable_write);
    return ret;
}

int EPollPoller::del_event(std::shared_ptr<Socket> sock) {
    struct epoll_event ev = { 0 };
    ev.data.ptr = sock->get_channel();
    ev.events = 0;
    int ret = epoll_ctl(m_epoll_fd, EPOLL_CTL_DEL, sock->get_handle(), &ev);
    INFO("epoll_ctl DEL: ret=%d, socket=%d", ret, sock->get_handle());
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