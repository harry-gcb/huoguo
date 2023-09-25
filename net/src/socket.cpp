#include "socket.h"
#include "logger.h"
#include <unistd.h>
#include <sys/socket.h>

namespace huoguo {
namespace net {

Socket::Socket(sa_family_t family, int type, int protocol)
    : m_family(family),
      m_fd(::socket(family, type, protocol)) {
    DEBUG("create fd, m_fd=%d, this=%p", m_fd, this);
}


Socket::Socket(int sock)
    : m_fd(sock) {
    DEBUG("accept fd, m_fd=%d, this=%p", m_fd, this);
}

Socket::~Socket() {
    ::close(m_fd);
    DEBUG("close fd, m_fd=%d, this=%p", m_fd, this);
}

int Socket::bind(const InetAddr &addr) {
    int ret = ::bind(m_fd, addr.get_addr(), static_cast<socklen_t>(sizeof(*addr.get_addr())));
    if (ret < 0) {
        FATAL("bind error: m_fd=%d, ret=%d, ip=%s, port=%d", m_fd, ret, addr.get_ip().c_str(), addr.get_port());
    }
    return ret;
}

int Socket::listen(int backlog) {
    int ret = ::listen(m_fd, backlog);
    if (ret < 0) {
        FATAL("listen error: m_fd=%d, ret=%d", m_fd, ret);
    }
    INFO("listen: m_fd=%d", m_fd);
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
    int fd = ::accept(m_fd, addr, addrlen);
    if (fd < 0) {
        ERROR("accept error: m_fd=%d, fd=%d", m_fd, fd);
        return nullptr;
    }
    return std::make_shared<Socket>(fd);
}

int Socket::connect(const struct sockaddr *addr, socklen_t addrlen) {
    return ::connect(m_fd, addr, addrlen);
}

int Socket::read(void *data, int len) {
    return ::read(m_fd, data, len);
}

int Socket::write(const void *data, int len) {
    return ::write(m_fd, data, len);
}

int Socket::recvfrom(void *data, int len, InetAddr &addr) {
    int n = 0;
    if (AF_INET6 == m_family) {
        struct sockaddr_in6 addr6 = { 0 };
        socklen_t addr6len = sizeof(addr6);
        n = ::recvfrom(m_fd, data, len, 0, (sockaddr *)&addr6, &addr6len);
        addr.from_inet_addr6(addr6);
    } else {
        struct sockaddr_in addr4 = { 0 };
        socklen_t addr4len = sizeof(addr4);
        n = ::recvfrom(m_fd, data, len, 0, (sockaddr *)&addr4, &addr4len);
        addr.from_inet_addr4(addr4);
    }
    return n;
}
int Socket::sendto(const void *data, int len, const InetAddr &addr) {
    return ::sendto(m_fd, data, len, 0, addr.get_addr(), addr.get_len());
}

int Socket::set_reuse_addr(bool reuse) {
    int optval = reuse ? 1 : 0;
    int ret = ::setsockopt(m_fd, SOL_SOCKET, SO_REUSEADDR, &optval, static_cast<socklen_t>(sizeof(optval)));
    if (ret < 0) {
        FATAL("set SO_REUSEADDR failed: m_fd=%d, ret=%d", m_fd, ret);
    }
    return ret;
}

int Socket::set_reuse_port(bool reuse) {
    int optval = reuse ? 1 : 0;
    int ret = ::setsockopt(m_fd, SOL_SOCKET, SO_REUSEPORT, &optval, static_cast<socklen_t>(sizeof(optval)));
    if (ret < 0) {
        FATAL("set SO_REUSEPORT failed: m_fd=%d, ret=%d", m_fd, ret);
    }
    return ret;
}

int Socket::get_fd() {
    return m_fd;
}

Channel *Socket::get_channel() {
    return m_channel;
}
void Socket::set_channel(Channel *channel) {
    m_channel = channel;
}

} // namespace net
} // namespace huoguo