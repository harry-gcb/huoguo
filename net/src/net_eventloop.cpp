#include "utils_logger.h"
#include "net_eventloop.h"
#include "net_poller_factory.h"
#include "net_wakeup_factory.h"
#include "net_channel.h"
#include "net_ioevent.h"
#include "net_poller.h"

namespace huoguo {
namespace net {

EventLoop::EventLoop()
    : m_stop(false),
      m_poller(PollerFactory::NewPoller()),
      m_event_io(WakeupFactory::NewWakeup()),
      m_channel(new Channel(this, m_event_io)) {
    m_channel->set_read_callback(std::bind(&EventLoop::handle_read_event, this));
    this->add_channel(m_channel);
    m_channel->enable_read(true);
}

EventLoop::~EventLoop() {
    m_channel->enable_all(false);
    this->del_channel(m_channel);
}

int EventLoop::run() {
    InfoL("EventLoop start running");
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
            // InfoL("[%s] active, read=%d, write=%d, error=%d", event->m_channel->get_trace_id().c_str(), event->m_read_occurred, event->m_write_occurred, event->m_error_occurred);
        }
        handle_close_event();
    }
    InfoL("EventLoop exit running");
    return 0;
}

void EventLoop::stop() {
    m_stop = true;
    active_read_event();
}

int EventLoop::add_channel(std::shared_ptr<Channel> channel) {
    return m_poller->add_event(channel->get_event(), channel->is_reading(), channel->is_writing());
}

int EventLoop::set_channel(std::shared_ptr<Channel> channel) {
    return m_poller->set_event(channel->get_event(), channel->is_reading(), channel->is_writing());
}

int EventLoop::del_channel(std::shared_ptr<Channel> channel) {
    return m_poller->del_event(channel->get_event());
}

void EventLoop::handle_read_event() {
    uint64_t one = 1;
    size_t n = m_event_io->read((uint8_t *)&one, sizeof(one));
    if (n != sizeof(one)) {
        ErrorL("read %d bytes instead of %d", n, sizeof(one));
    }
}

void EventLoop::active_read_event() {
    uint64_t one = 1;
    size_t n = m_event_io->write((const uint8_t *)&one, sizeof(one));
    if (n != sizeof(one)) {
        ErrorL("read %d bytes instead of %d", n, sizeof(one));
    }
}

void EventLoop::push_close_event(Callback callback) {
    m_callback.push_back(callback);
    active_read_event();
}

void EventLoop::handle_close_event() {
    for (auto callback: m_callback) {
        callback();
    }
    m_callback.clear();
}

} // namespace net
} // namespace huoguo