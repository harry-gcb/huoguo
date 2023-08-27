#include "channel.h"
#include "event_loop.h"
#include "logger.h"
#include "uuid.h"

namespace huoguo {
namespace net {

Channel::Channel(EventLoop *loop, std::shared_ptr<EventIO> event)
    : m_loop(loop),
      m_event(event),
      m_enable_read(false),
      m_enable_write(false),
      m_channel_id(huoguo::utils::uuid::generate()) {
    m_event->set_channel(this);
    INFO("channel=%s, this=%p", m_channel_id.c_str(), this);
}

Channel::~Channel() {
    INFO("channel=%s, this=%p", m_channel_id.c_str(), this);
}

std::string Channel::get_channel_id() const {
    return m_channel_id;
}

std::shared_ptr<EventIO> Channel::get_event() {
    return m_event;
}

void Channel::set_read_callback(EventCallback callback) {
    m_read_callback = callback;
}

void Channel::set_write_callback(EventCallback callback) {
    m_write_callback = callback;
}
void Channel::set_close_callback(EventCallback callback) {
    m_close_callback = callback;
}

void Channel::set_error_callback(EventCallback callback) {
    m_error_callback = callback;
}

void Channel::handle_read_event() {
    if (m_read_callback) {
        m_read_callback();
    }
}

void Channel::handle_write_event() {
    if (m_write_callback) {
        m_write_callback();
    }
}

void Channel::handle_close_event() {
    if (m_close_callback) {
        m_close_callback();
    }
}

void Channel::handle_error_event() {
    if (m_error_callback) {
        m_error_callback();
    }
}


void Channel::enable_read(bool enable) {
    m_enable_read = enable;
    m_loop->set_channel(shared_from_this());
}
void Channel::enable_write(bool enable) {
    m_enable_write = enable;
    m_loop->set_channel(shared_from_this());
}

void Channel::enable_all(bool enable) {
    m_enable_read = enable;
    m_enable_write = enable;
    m_loop->set_channel(shared_from_this());
}

bool Channel::is_reading() {
    return m_enable_read;
}

bool Channel::is_writing() {
    return m_enable_write;
}

} // namespace net
} // namespace huoguo