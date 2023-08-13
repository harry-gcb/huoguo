#include "tcp_server.h"
#include "acceptor.h"

namespace huoguo {
namespace net {

TcpServer::TcpServer(EventLoop *loop, const InetAddr &addr, const std::string &name, bool reuse) 
    : m_loop(loop),
      m_acceptor(new Acceptor(loop, addr, reuse)) {

}

void TcpServer::start() {

}

void TcpServer::set_connect_callback(const ConnectCallback &cb) {
    m_connect_callback = cb;
}
void TcpServer::set_message_callback(const MessageCallback &cb) {
    m_message_callback = cb;
}

} // namespace net
} // namespace huoguo