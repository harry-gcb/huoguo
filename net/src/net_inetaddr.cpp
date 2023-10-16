#include <cstring>
#include "utils.h"
#include "net_inetaddr.h"

namespace huoguo {
namespace net {

static const int addr_len = 128;

#define IPV6_ANY        "::"
#define IPV6_LOOPBACK   "::1"
#define IPV4_ANY        "0.0.0.0"
#define IPV4_LOOPBACK   "127.0.0.1"

InetAddr::InetAddr()
    : m_addr_type(AF_INET),
      m_addr_protocol(SOCK_STREAM),
      m_addr_family(IPPROTO_TCP) {
};

InetAddr::InetAddr(uint16_t port, const std::string &ip, bool loopback, bool udp, bool ipv6)
    : m_addr_type(udp ? SOCK_DGRAM : SOCK_STREAM),
      m_addr_protocol(udp ? IPPROTO_UDP : IPPROTO_TCP),
      m_addr_port(port) {
    if (ip.empty()) {
        if (     !ipv6 &&  loopback)    { m_addr_ip = IPV4_LOOPBACK; }
        else if (!ipv6 && !loopback)    { m_addr_ip = IPV4_ANY; }
        else if ( ipv6 &&  loopback)    { m_addr_ip = IPV6_LOOPBACK; }
        else if ( ipv6 && !loopback)    { m_addr_ip = IPV6_ANY; }
        else { ErrorL("unsupport protocol, ipv6=%d, lookback=%d", ipv6, loopback); }
    } else {
        ipv6 = ip.find(":") != std::string::npos;
        m_addr_ip = ip;
    }
    m_addr_family = ipv6 ? AF_INET6 : AF_INET;
    if (ipv6) {
        memset(&m_addr_v6, 0, sizeof(m_addr_v6));
        m_addr_v6.sin6_family = m_addr_family;
        inet_pton(m_addr_family, m_addr_ip.c_str(), &m_addr_v6.sin6_addr);
        m_addr_v6.sin6_port = htons(port);
    } else {
        memset(&m_addr_v4, 0, sizeof(m_addr_v4));
        m_addr_v4.sin_family = m_addr_family;
        inet_pton(m_addr_family, m_addr_ip.c_str(), &m_addr_v4.sin_addr);
        // addr4.sin_addr.s_addr = inet_addr(m_addr_ip.c_str());
        m_addr_v4.sin_port = htons(port);
    }
}

InetAddr::InetAddr(const std::string &ip, uint16_t port, bool udp)
    : m_addr_type(udp ? SOCK_DGRAM : SOCK_STREAM),
      m_addr_protocol(udp ? IPPROTO_UDP : IPPROTO_TCP),
      m_addr_port(port),
      m_addr_ip(ip),
      m_addr_family(ip.find(":") != std::string::npos ? AF_INET6 : AF_INET) {    
    if (m_addr_family == AF_INET6) {
        memset(&m_addr_v6, 0, sizeof(m_addr_v6));
        m_addr_v6.sin6_family = m_addr_family;
        inet_pton(m_addr_family, m_addr_ip.c_str(), &m_addr_v6.sin6_addr);
        m_addr_v6.sin6_port = htons(port);
    } else {
        memset(&m_addr_v4, 0, sizeof(m_addr_v4));
        m_addr_v4.sin_family = m_addr_family;
        inet_pton(m_addr_family, m_addr_ip.c_str(), &m_addr_v4.sin_addr);
        // addr4.sin_addr.s_addr = inet_addr(m_addr_ip.c_str());
        m_addr_v4.sin_port = htons(port);
    }
}

InetAddr::InetAddr(const struct sockaddr_in& addr4)
    : m_addr_type(SOCK_STREAM),
      m_addr_protocol(IPPROTO_TCP),
      m_addr_port(ntohs(addr4.sin_port)),
      m_addr_family(addr4.sin_family),
      m_addr_v4(addr4) {
    char buf[addr_len] = { 0 };
    inet_ntop(m_addr_family, &m_addr_v4.sin_addr, buf, addr_len);
    m_addr_ip = std::string(buf);
}

InetAddr::InetAddr(const struct sockaddr_in6& addr6)
    : m_addr_type(SOCK_STREAM),
      m_addr_protocol(IPPROTO_TCP),
      m_addr_port(ntohs(addr6.sin6_port)),
      m_addr_family(addr6.sin6_family),
      m_addr_v6(addr6) {
    char buf[addr_len] = { 0 };
    inet_ntop(m_addr_family, &m_addr_v6.sin6_addr, buf, addr_len);
    m_addr_ip = std::string(buf);
}

int InetAddr::from_inet_addr4(const struct sockaddr_in& addr4) {
    m_addr_port = ntohs(addr4.sin_port),
    m_addr_family = addr4.sin_family;
    m_addr_v4 = addr4;
    char buf[addr_len] = { 0 };
    inet_ntop(m_addr_family, &m_addr_v4.sin_addr, buf, addr_len);
    m_addr_ip = std::string(buf);
    return 0;
}

int InetAddr::from_inet_addr6(const struct sockaddr_in6& addr6) {
    m_addr_port = ntohs(addr6.sin6_port),
    m_addr_family = addr6.sin6_family;
    m_addr_v6 = addr6;
    char buf[addr_len] = { 0 };
    inet_ntop(m_addr_family, &m_addr_v6.sin6_addr, buf, addr_len);
    m_addr_ip = std::string(buf);
    return 0;
}

InetAddr InetAddr::get_local_addr(int fd, bool ipv6) {
    if (ipv6) {
        struct sockaddr_in6 local_addr = { 0 };
        socklen_t addrlen = static_cast<socklen_t>(sizeof(local_addr));
        int ret = ::getsockname(fd, reinterpret_cast<struct sockaddr*>(&local_addr), &addrlen);
        return InetAddr(local_addr);
    } else {
        struct sockaddr_in local_addr = { 0 };
        socklen_t addrlen = static_cast<socklen_t>(sizeof(local_addr));
        int ret = getsockname(fd, reinterpret_cast<struct sockaddr*>(&local_addr), &addrlen);
        return InetAddr(local_addr);
    }
}

InetAddr InetAddr::get_remote_addr(int fd, bool ipv6) {
    if (ipv6) {
        struct sockaddr_in6 local_addr = { 0 };
        socklen_t addrlen = static_cast<socklen_t>(sizeof(local_addr));
        int ret = ::getpeername(fd, reinterpret_cast<struct sockaddr*>(&local_addr), &addrlen);
        return InetAddr(local_addr);
    } else {
        struct sockaddr_in local_addr = { 0 };
        socklen_t addrlen = static_cast<socklen_t>(sizeof(local_addr));
        int ret = getpeername(fd, reinterpret_cast<struct sockaddr*>(&local_addr), &addrlen);
        return InetAddr(local_addr);
    }
}

const sockaddr *InetAddr::get_addr() const {
    return m_addr_family == AF_INET ? reinterpret_cast<const sockaddr *>(&m_addr_v4)
                                    : reinterpret_cast<const sockaddr *>(&m_addr_v6);
}

socklen_t InetAddr::get_len() const {
    return m_addr_family == AF_INET ? sizeof(m_addr_v4) : sizeof(m_addr_v6);
}

sa_family_t InetAddr::get_family() const {
    return m_addr_family;
}
int InetAddr::get_type() const {
    return m_addr_type;
}
int InetAddr::get_protocol() const {
    return m_addr_protocol;
}

std::string InetAddr::get_ip() const {
    return m_addr_ip;
}

int InetAddr::get_port() const {
    return m_addr_port;
}

} // namespace net
} // namespace huoguo