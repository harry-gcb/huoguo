#include "net_udpclient.h"
#include "net_socket.h"

namespace huoguo {
namespace net {

UdpClient::UdpClient(EventLoop *loop, const InetAddr &addr, const std::string &name)
    : m_loop(loop),
      m_inet_addr(addr) {
    auto socket = std::make_shared<Socket>(addr.get_family(), addr.get_type(), addr.get_protocol());
    // socket->bind
    m_connection = std::make_shared<UdpConnection>(m_loop, socket);
}

UdpClient::~UdpClient() {
}

void UdpClient::start() {
}

void UdpClient::set_message_callback(DatagramCallback callback) {
    m_connection->set_message_callback(callback);
}

int UdpClient::sendto(const InetAddr &addr, const std::string &buffer) {
    return m_connection->sendto(addr, buffer);
}

int UdpClient::sendto(const InetAddr &addr, const char *buffer, int length) {
    return m_connection->sendto(addr, buffer, length);
}


}
}