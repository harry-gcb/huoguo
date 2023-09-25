#include "udp_server.h"
#include "socket.h"
#include "logger.h"

namespace huoguo {
namespace net {

UdpServer::UdpServer(EventLoop *loop, const InetAddr &addr, const std::string &name, bool reuse)
    : m_loop(loop),
      m_inet_addr(addr) {
    auto socket = std::make_shared<Socket>(addr.get_family(), addr.get_type(), addr.get_protocol());
    socket->bind(m_inet_addr);
    m_connection = std::make_shared<UdpConnection>(m_loop, socket);
}

UdpServer::~UdpServer() {
}

void UdpServer::set_datagram_callback(DatagramCallback callback) {
    m_connection->set_datagram_callback(callback);
}

}
}