// #include "utils.h"
#include "net_tcpserver.h"
#include "net_acceptor.h"
#include "net_socket.h"
#include "net_tcpconnection.h"
#include "net_eventloop.h"

namespace huoguo {
namespace net {

TcpServer::TcpServer(EventLoop *loop, const InetAddr &addr, const std::string &name, bool reuse) 
    : m_loop(loop),
      m_acceptor(new Acceptor(loop, addr, reuse)),
      m_server_addr(addr),
      m_server_name(name),
      m_conn_id(0),
      m_connect_callback(default_connect_callback),
      m_message_callback(default_message_callback) {
    m_acceptor->set_establish_callback(std::bind(&TcpServer::add_connection, this, std::placeholders::_1));
}

TcpServer::~TcpServer() {
    for (auto &item: m_connections) {
        std::shared_ptr<TcpConnection> conn(item.second);
        conn->shutdown();
    }
}

void TcpServer::start() {
    m_acceptor->listen();
}

void TcpServer::set_connect_callback(const ConnectCallback &cb) {
    m_connect_callback = cb;
}
void TcpServer::set_message_callback(const SegmentCallback &cb) {
    m_message_callback = cb;
}

void TcpServer::add_connection(std::shared_ptr<Socket> sock) {
    InetAddr local_addr = InetAddr::get_local_addr(sock->get_fd());
    InetAddr remote_addr = InetAddr::get_remote_addr(sock->get_fd());
    auto conn = std::make_shared<TcpConnection>(m_loop, sock, local_addr, remote_addr);
    conn->set_connect_callback(m_connect_callback);
    conn->set_message_callback(m_message_callback);
    conn->set_close_callback(std::bind(&TcpServer::del_connection, this, std::placeholders::_1));
    m_connections[conn->get_trace_id()] = conn;
    conn->establish();
}

void TcpServer::del_connection(std::shared_ptr<TcpConnection> conn) {
    m_loop->push_close_event([this, conn]{
        conn->shutdown();
        m_connections.erase(conn->get_trace_id());
    });
}


} // namespace net
} // namespace huoguo