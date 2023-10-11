#include "utils.h"
#include "net_udpconnection.h"
#include "net_eventloop.h"
#include "net_socket.h"
#include "net_channel.h"

namespace huoguo {
namespace net {

UdpConnection::UdpConnection(EventLoop *loop, std::shared_ptr<Socket> sock)
    : m_loop(loop),
      m_socket(sock),
      m_channel(new Channel(loop, m_socket)),
      m_trace_id(m_channel->get_trace_id()) {
    memset(m_buffer, 0, sizeof(m_buffer));
    m_channel->set_read_callback(std::bind(&UdpConnection::handle_read_event, this));
    m_channel->set_error_callback(std::bind(&UdpConnection::handle_error_event, this));
    m_loop->add_channel(m_channel);
    m_channel->enable_read(true);
    INFO("[%s] UdpConnection ctor, this=%p", m_trace_id.c_str(), this);
}

UdpConnection::~UdpConnection() {
    m_channel->enable_all(false);
    m_loop->del_channel(m_channel);
    INFO("[%s] ~UdpConnection dtor, this=%p", m_trace_id.c_str(), this);
}

int UdpConnection::sendto(const std::string &buffer, const InetAddr &remote_addr) {
    return m_socket->sendto(buffer.data(), buffer.length(), remote_addr);
}

void UdpConnection::set_datagram_callback(DatagramCallback callback) {
    m_datagram_callback = callback;
}

void UdpConnection::handle_read_event() {
    size_t n = m_socket->recvfrom(m_buffer, BUF_SIZE, m_remote_addr);
    if (n > 0) {
        m_datagram_callback(shared_from_this(), m_buffer, n);
    }
}

void UdpConnection::handle_error_event() {
}

std::string UdpConnection::get_trace_id() const {
    return m_trace_id;
}

// std::string UdpConnection::get_local_ip() const {
//     return m_local_addr.get_ip();
// }

// int UdpConnection::get_local_port() const {
//     return m_local_addr.get_port();
// }

// std::string UdpConnection::get_remote_ip() const {
//     return m_remote_addr.get_ip();
// }

// int UdpConnection::get_remote_port() const {
//     return m_remote_addr.get_port();
// }


} // namespace net
} // namespace huoguo