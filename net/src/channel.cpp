#include "channel.h"
#include "event_loop.h"

namespace huoguo {
namespace net {

Channel::Channel(EventLoop *loop, std::shared_ptr<Socket> sock)
    : m_loop(loop),
      m_socket(sock),
      m_enable_read(false),
      m_enable_write(false) {
}

std::shared_ptr<Socket> Channel::get_socket() {
    return m_socket;
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

void Channel::enable_read_event() {
    m_enable_read = true;
    m_loop->set_channel(shared_from_this());
}

void Channel::disable_read_event() {
    m_enable_read = false;
    m_loop->set_channel(shared_from_this());
}
void Channel::enable_write_event() {
    m_enable_write = true;
    m_loop->set_channel(shared_from_this());
}

void Channel::disable_write_event() {
    m_enable_write = false;
    m_loop->set_channel(shared_from_this());
}

bool Channel::enable_read() {
    return m_enable_read;
}

bool Channel::enable_write() {
    return m_enable_write;
}

} // namespace net
} // namespace huoguo
