#include "event_loop.h"
#include "logger.h"
#include "poller_factory.h"
#include "epoll_poller.h"
#include "channel.h"

namespace huoguo {
namespace net {

EventLoop::EventLoop()
    : m_stop(false),
      m_poller(PollerFactory::NewPoller()) {
}

EventLoop::~EventLoop() {

}

int EventLoop::run() {
    INFO("EventLoop start running");
    while (!m_stop) {
        std::list<std::shared_ptr<IOEvent>> ioevents;
        int ret = m_poller->get_event(ioevents, 1000);
        for (auto &event: ioevents) {
            if (event->m_read_occurred) {
                event->m_channel->handle_read_event();
            }
            if (event->m_write_occurred) {
                event->m_channel->handle_write_event();
            }
            if (event->m_error_occurred) {
                event->m_channel->handle_error_event();
            }
        }
        DEBUG("EventLoop handle %d events", ret);
    }
    INFO("EventLoop exit running");
    return 0;
}

int EventLoop::add_channel(std::shared_ptr<Channel> channel) {
    return m_poller->add_event(channel->get_socket(), channel->enable_read(), channel->enable_write());
}

int EventLoop::set_channel(std::shared_ptr<Channel> channel) {
    return m_poller->set_event(channel->get_socket(), channel->enable_read(), channel->enable_write());
}

int EventLoop::del_channel(std::shared_ptr<Channel> channel) {
    return m_poller->del_event(channel->get_socket());
}

} // namespace net
} // namespace huoguo