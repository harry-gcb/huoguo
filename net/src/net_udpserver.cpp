#include "utils.h"
#include "net_socket.h"
#include "net_udpserver.h"

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

void UdpServer::start() {

}

void UdpServer::set_message_callback(DatagramCallback callback) {
    m_connection->set_message_callback(callback);
}

int UdpServer::sendto(const InetAddr &addr, const std::string &buffer) {
    return m_connection->sendto(addr, buffer);
}

int UdpServer::sendto(const InetAddr &addr, const char *buffer, int length) {
    return m_connection->sendto(addr, buffer, length);
}

}
}