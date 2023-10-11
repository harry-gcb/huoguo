#include "utils.h"

#include "net_tcpclient.h"
#include "net_eventloop.h"
#include "net_socket.h"
#include "net_connector.h"
#include "net_tcpconnection.h"

namespace huoguo {
namespace net {

TcpClient::TcpClient(EventLoop *loop, const InetAddr &addr, const std::string &name)
    : m_loop(loop),
      m_connector(new Connector(loop, addr)),
      m_client_addr(addr),
      m_client_name(name),
      m_conn_id(0),
      m_connect_callback(default_connect_callback),
      m_message_callback(default_message_callback) {
    m_connector->set_establish_callback(std::bind(&TcpClient::add_connection, this, std::placeholders::_1));
}

void TcpClient::start() {
    m_connector->connect();
}

void TcpClient::set_connect_callback(const ConnectCallback &cb) {
    m_connect_callback = cb;
}

void TcpClient::set_message_callback(const MessageCallback &cb) {
    m_message_callback = cb;
}

void TcpClient::add_connection(std::shared_ptr<Socket> sock) {
    InetAddr local_addr = InetAddr::get_local_addr(sock->get_fd());
    InetAddr remote_addr = InetAddr::get_remote_addr(sock->get_fd());
    m_connection = std::make_shared<TcpConnection>(m_loop, sock, local_addr, remote_addr);
    m_connection->set_connect_callback(m_connect_callback);
    m_connection->set_message_callback(m_message_callback);
    m_connection->set_close_callback(std::bind(&TcpClient::del_connection, this, std::placeholders::_1));
    m_connection->establish();
}

void TcpClient::del_connection(std::shared_ptr<TcpConnection> conn) {
    m_loop->push_close_event([this, conn]{
        conn->shutdown();
        m_connection.reset();
    });
}

}
}