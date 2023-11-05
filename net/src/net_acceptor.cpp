#include "utils_logger.h"
#include "net_acceptor.h"
#include "net_socket.h"
#include "net_channel.h"
#include "net_eventloop.h"

namespace huoguo {
namespace net {

Acceptor::Acceptor(EventLoop *loop, const InetAddr &addr, bool reuse)
    : m_loop(loop),
      m_listening(false) {
    m_socket = std::make_shared<Socket>(addr.get_family(), addr.get_type(), addr.get_protocol());
    m_socket->set_reuse_addr(true);
    m_socket->set_reuse_port(reuse);
    m_socket->bind(addr);
    m_channel = std::make_shared<Channel>(loop, m_socket);
    m_channel->set_read_callback(std::bind(&Acceptor::handle_read_event, this));
}

Acceptor::~Acceptor() {
    if (m_listening) {
        m_loop->del_channel(m_channel);
        m_listening = false;
    }
}

void Acceptor::listen() {
    if (m_listening) {
        return;
    }
    m_listening = true;
    m_socket->listen();
    m_loop->add_channel(m_channel);
    m_channel->enable_read(true);
    InfoL("listen and enable read");
}

void Acceptor::set_establish_callback(EstablishCallback callback) {
    m_establish_callback = callback;
}

void Acceptor::handle_read_event() {
    auto sock = m_socket->accept();
    if (sock) {
        if (m_establish_callback) {
            InfoL("accept a new connection");
            m_establish_callback(sock);
        } else {
            WarnL("no establish callback for %d", sock->get_fd());
        }
    } else {
        ErrorL("error for accept");
    }
}

} // namespace 
}