#include "net_connector.h"
#include "net_socket.h"

namespace huoguo {
namespace net {

Connector::Connector(EventLoop *loop, const InetAddr &addr)
    : m_loop(loop),
      m_connecting(false),
      m_addr(addr) {
}

Connector::~Connector() {
    // m_loop->del_channel(m_channel);
}

void Connector::connect() {
    if (m_connecting) {
        return;
    }
    m_connecting = true;
    socklen_t addrlen = m_addr.get_len();
    DebugL("connect to peer, ip=%s, port=%d, family=%d, type=%d, protocol=%d", m_addr.get_ip().c_str(), m_addr.get_port(), m_addr.get_family(), m_addr.get_type(), m_addr.get_protocol());
    auto sock = std::make_shared<Socket>(m_addr.get_family(), m_addr.get_type(), m_addr.get_protocol());
    int ret = sock->connect(m_addr.get_addr(), addrlen);
    if (ret == 0) {
        m_establish_callback(sock);
    } else {
        ErrorL("ip=%s, port=%d, return=%d, errno=%d", m_addr.get_ip().c_str(), m_addr.get_port(), ret, errno);
    }
}

void Connector::set_establish_callback(EstablishCallback callback) {
    m_establish_callback = callback;
}

void Connector::handle_read_event() {

}

}
}