#include "utils_logger.h"
#include "net_socket.h"

namespace huoguo {
namespace net {

Socket::Socket(sa_family_t family, int type, int protocol)
    : m_family(family),
      m_fd(static_cast<int>(::socket(family, type, protocol))) {
    DebugL("create fd, m_fd=%d, this=%p", m_fd, this);
}


Socket::Socket(int sock)
    : m_fd(sock) {
    DebugL("Socket, m_fd=%d, this=%p", m_fd, this);
}

Socket::~Socket() {
#ifdef _WIN32
    ::closesocket(m_fd);
#else
    ::close(m_fd);
#endif
    DebugL("close fd, m_fd=%d, this=%p", m_fd, this);
}

int Socket::bind(const InetAddr &addr) {
    int ret = ::bind(m_fd, addr.get_addr(), static_cast<socklen_t>(sizeof(*addr.get_addr())));
    if (ret < 0) {
        FatalL("bind error: m_fd=%d, ret=%d, ip=%s, port=%d", m_fd, ret, addr.get_ip().c_str(), addr.get_port());
        return ret;
    }
    InfoL("bind success: m_fd=%d, ret=%d, ip=%s, port=%d", m_fd, ret, addr.get_ip().c_str(), addr.get_port());
    return ret;
}

int Socket::listen(int backlog) {
    int ret = ::listen(m_fd, backlog);
    if (ret < 0) {
        FatalL("listen error: m_fd=%d, ret=%d", m_fd, ret);
        return ret;
    }
    InfoL("listen success: m_fd=%d", m_fd);
    return ret;
}

std::shared_ptr<Socket> Socket::accept() {
    int ret = 0;
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
    int fd = static_cast<int>(::accept(m_fd, addr, addrlen));
    if (fd < 0) {
        ErrorL("accept error: m_fd=%d, fd=%d", m_fd, fd);
        return nullptr;
    }
    InfoL("accept success: m_fd=%d, fd=%d", m_fd, fd);
    return std::make_shared<Socket>(fd);
}

int Socket::connect(const InetAddr &addr) {
    int ret = this->connect(addr.get_addr(), static_cast<socklen_t>(sizeof(*addr.get_addr())));
    InfoL("connect: m_fd=%d, ret=%d, ip=%s, port=%d", m_fd, ret, addr.get_ip().c_str(), addr.get_port());
    return ret;
}

int Socket::connect(const struct sockaddr *addr, socklen_t addrlen) {
    int ret = ::connect(m_fd, addr, addrlen);
    return ret;
}

int Socket::read(uint8_t *data, size_t size) {
#ifdef _WIN32
    return ::recv(m_fd, (char *)data, size, 0);
#else
    return ::read(m_fd, data, len);
#endif
}

int Socket::write(const uint8_t *data, size_t size) {
#ifdef _WIN32
    return ::send(m_fd, (char *)data, size, 0);
#else
    return ::write(m_fd, data, len);
#endif
    
}

int Socket::recvfrom(uint8_t *data, size_t size, InetAddr &addr) {
    int n = 0;
    if (AF_INET6 == m_family) {
        struct sockaddr_in6 addr6 = { 0 };
        socklen_t addr6len = sizeof(addr6);
        n = ::recvfrom(m_fd, (char *)data, size, 0, (sockaddr *)&addr6, &addr6len);
        addr.from_inet_addr6(addr6);
    } else {
        struct sockaddr_in addr4 = { 0 };
        socklen_t addr4len = sizeof(addr4);
        n = ::recvfrom(m_fd, (char *)data, size, 0, (sockaddr *)&addr4, &addr4len);
        addr.from_inet_addr4(addr4);
    }
    return n;
}
int Socket::sendto(const uint8_t *data, size_t size, const InetAddr &addr) {
    return ::sendto(m_fd, (char *)data, size, 0, addr.get_addr(), addr.get_len());
}

int Socket::set_reuse_addr(bool reuse) {
    int optval = reuse ? 1 : 0;
#ifdef _WIN32
    int ret = ::setsockopt(m_fd, SOL_SOCKET, SO_REUSEADDR, (const char *)&optval, static_cast<socklen_t>(sizeof(optval)));
#else
    int ret = ::setsockopt(m_fd, SOL_SOCKET, SO_REUSEADDR, &optval, static_cast<socklen_t>(sizeof(optval)));
#endif
    if (ret < 0) {
        FatalL("set SO_REUSEADDR failed: m_fd=%d, ret=%d", m_fd, ret);
    }
    return ret;
}

int Socket::set_reuse_port(bool reuse) {
#ifdef _WIN32
    return 0;
#else
    int optval = reuse ? 1 : 0;
    int ret = ::setsockopt(m_fd, SOL_SOCKET, SO_REUSEPORT, &optval, static_cast<socklen_t>(sizeof(optval)));

    if (ret < 0) {
        FatalL("set SO_REUSEPORT failed: m_fd=%d, ret=%d", m_fd, ret);
    }
    return ret;
#endif
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