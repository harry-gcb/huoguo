#include "tcp_connection.h"
#include "event_loop.h"
#include "channel.h"
#include "logger.h"

namespace huoguo {
namespace net {

TcpConnection::TcpConnection(EventLoop *loop, std::shared_ptr<Socket> sock, const InetAddr &local_addr, const InetAddr &remote_addr)
    : m_loop(loop),
      m_socket(sock),
      m_channel(new Channel(loop, m_socket)),
      m_local_addr(local_addr),
      m_remote_addr(remote_addr),
      m_connected(false) {
    m_channel->set_read_callback(std::bind(&TcpConnection::handle_read_event, this));
    m_channel->set_write_callback(std::bind(&TcpConnection::handle_write_event, this));
    m_channel->set_close_callback(std::bind(&TcpConnection::handle_close_event, this));
    m_channel->set_error_callback(std::bind(&TcpConnection::handle_error_event, this));
    m_loop->add_channel(m_channel);
}

TcpConnection::~TcpConnection() {
    m_loop->del_channel(m_channel);
}

void TcpConnection::establish() {
    m_connected = true;
    if (m_connect_callback) {
        m_connect_callback(shared_from_this());
    }
    m_channel->enable_read(true);
}

void TcpConnection::shutdown() {
    if (m_connected) {
        m_connected = false;
        m_channel->enable_all(false);
        if (m_connect_callback) {
            m_connect_callback(shared_from_this());
        }
    }
}

void TcpConnection::set_connect_callback(ConnectCallback callback) {
    m_connect_callback = callback;
}

void TcpConnection::set_message_callback(MessageCallback callback) {
    m_message_callback = callback;
}

void TcpConnection::set_close_callback(CloseCallback callback) {
    m_close_callback = callback;
}

void TcpConnection::handle_read_event() {
    const int len = 4096;
    char data[len] = { 0 };
    size_t n = m_socket->read(data, len);
    if (n > 0) {
        m_message_callback(shared_from_this());
    } else if (n == 0) {
        handle_close_event();
    } else {
        handle_error_event();
    }
}

void TcpConnection::handle_write_event() {

}
void TcpConnection::handle_close_event() {
    m_close_callback(shared_from_this());
}

void TcpConnection::handle_error_event() {
    m_close_callback(shared_from_this());
}

std::string TcpConnection::get_name() const {
    return m_channel->get_channel_id();
}

std::string TcpConnection::get_local_ip() const {
    return m_local_addr.get_ip();
}

int TcpConnection::get_local_port() const {
    return m_local_addr.get_port();
}

std::string TcpConnection::get_remote_ip() const {
    return m_remote_addr.get_ip();
}

int TcpConnection::get_remote_port() const {
    return m_remote_addr.get_port();
}

bool TcpConnection::is_connected() {
    return m_connected;
}

} // namespace net
} // namespace huoguo