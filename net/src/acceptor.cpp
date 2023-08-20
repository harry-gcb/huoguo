#include "acceptor.h"
#include "event_loop.h"
#include "socket.h"
#include "logger.h"
#include "channel.h"

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
    m_socket->set_channel(m_channel.get());
    m_loop->add_channel(m_channel);
}

Acceptor::~Acceptor() {
    m_loop->del_channel(m_channel);
}

void Acceptor::listen() {
    m_listening = true;
    m_socket->listen();
    m_channel->enable_read_event();
    INFO("listen and enable read");
}

void Acceptor::set_establish_callback(EstablishCallback callback) {
    m_establish_callback = callback;
}

void Acceptor::handle_read_event() {
    auto sock = m_socket->accept();
    if (sock) {
        if (m_establish_callback) {
            INFO("accept a new connection");
            m_establish_callback(sock);
        } else {
            WARN("no establish callback for %d", sock->get_handle());
        }
    } else {
        ERROR("error for accept");
    }
}

} // namespace 
}