#include "socket.h"
#include "logger.h"
#include <unistd.h>
#include <sys/socket.h>

namespace huoguo {
namespace net {

Socket::Socket(sa_family_t family, int type, int protocol)
    : m_family(family),
      m_socket(::socket(family, type, protocol)) {
}


Socket::Socket(int sock)
    : m_socket(sock) {
}

Socket::~Socket() {
    ::close(m_socket);
}

int Socket::bind(const InetAddr &addr) {
    int ret = ::bind(m_socket, addr.get_addr(), static_cast<socklen_t>(sizeof(*addr.get_addr())));
    if (ret < 0) {
        FATAL("bind error: m_socket=%d, ret=%d, ip=%s, port=%d", m_socket, ret, addr.get_ip().c_str(), addr.get_port());
    }
    return ret;
}

int Socket::listen(int backlog) {
    int ret = ::listen(m_socket, backlog);
    if (ret < 0) {
        FATAL("listen error: m_socket=%d, ret=%d", m_socket, ret);
    }
    INFO("listen: m_socket=%d", m_socket);
    return ret;
}

std::shared_ptr<Socket> Socket::accept() {
    if (AF_INET6 == m_family) {
        struct sockaddr_in6 addr = { 0 };
        socklen_t addrlen = sizeof(addr);
        return this->accept(reinterpret_cast<sockaddr *>(&addr), &addrlen);
    } else {
        struct sockaddr_in addr = { 0 };
        socklen_t addrlen = sizeof(addr);
        return this->accept(reinterpret_cast<sockaddr *>(&addr), &addrlen);
    }
}

std::shared_ptr<Socket> Socket::accept(struct sockaddr *addr, socklen_t *addrlen) {
    int fd = ::accept(m_socket, addr, addrlen);
    if (fd < 0) {
        ERROR("accept error: m_socket=%d, fd=%d", m_socket, fd);
        return nullptr;
    }
    return std::make_shared<Socket>(fd);
}

int Socket::connect(const struct sockaddr *addr, socklen_t addrlen) {
    return ::connect(m_socket, addr, addrlen);
}


int Socket::read(void *data, int len) {
    return ::read(m_socket, data, len);
}

int Socket::write(const void *data, int len) {
    return ::write(m_socket, data, len);
}

int Socket::set_reuse_addr(bool reuse) {
    int optval = reuse ? 1 : 0;
    int ret = ::setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, &optval, static_cast<socklen_t>(sizeof(optval)));
    if (ret < 0) {
        FATAL("set SO_REUSEADDR failed: m_socket=%d, ret=%d", m_socket, ret);
    }
    return ret;
}

int Socket::set_reuse_port(bool reuse) {
    int optval = reuse ? 1 : 0;
    int ret = ::setsockopt(m_socket, SOL_SOCKET, SO_REUSEPORT, &optval, static_cast<socklen_t>(sizeof(optval)));
    if (ret < 0) {
        FATAL("set SO_REUSEPORT failed: m_socket=%d, ret=%d", m_socket, ret);
    }
    return ret;
}

int Socket::get_handle() {
    return m_socket;
}

Channel *Socket::get_channel() {
    return m_channel;
}
void Socket::set_channel(Channel *channel) {
    m_channel = channel;
}

} // namespace net
} // namespace huoguo