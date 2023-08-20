#include "tcp_server.h"
#include "acceptor.h"
#include "socket.h"
#include "logger.h"
#include "tcp_connection.h"

namespace huoguo {
namespace net {

TcpServer::TcpServer(EventLoop *loop, const InetAddr &addr, const std::string &name, bool reuse) 
    : m_loop(loop),
      m_acceptor(new Acceptor(loop, addr, reuse)),
      m_server_addr(addr),
      m_server_name(name),
      m_conn_id(0) {
    m_acceptor->set_establish_callback(std::bind(&TcpServer::add_connection, this, std::placeholders::_1));
}

TcpServer::~TcpServer() {
    for (auto &item: m_connections) {
        TcpConnectionPtr conn(item.second);
        conn->shutdown();
    }
}

void TcpServer::start() {
    INFO("TcpServer start: name=%s, ip=%s, port=%d", m_server_name.c_str(), m_server_addr.get_ip().c_str(), m_server_addr.get_port());
    m_acceptor->listen();
}

void TcpServer::add_connection(std::shared_ptr<Socket> sock) {
    char name[128] = { 0 };
    snprintf(name, sizeof(name), "%s-%s#%lu", m_server_name.c_str(), m_server_addr.get_ip().c_str(), m_conn_id++);
    InetAddr local_addr = InetAddr::get_local_addr(sock->get_handle());
    InetAddr remote_addr = InetAddr::get_remote_addr(sock->get_handle());
    auto conn = std::make_shared<TcpConnection>(m_loop, name, sock, local_addr, remote_addr);
    conn->set_connect_callback(m_connect_callback);
    conn->set_message_callback(m_message_callback);
    conn->set_close_callback(std::bind(&TcpServer::del_connection, this, std::placeholders::_1));
    m_connections[name] = conn;
    conn->establish();
}

void TcpServer::del_connection(TcpConnectionPtr conn) {
    m_connections.erase(conn->get_name());
}

void TcpServer::set_connect_callback(const ConnectCallback &cb) {
    m_connect_callback = cb;
}
void TcpServer::set_message_callback(const MessageCallback &cb) {
    m_message_callback = cb;
}

} // namespace net
} // namespace huoguo