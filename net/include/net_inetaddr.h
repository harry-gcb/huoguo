#ifndef HUOGUO_NET_INETADDR_H_
#define HUOGUO_NET_INETADDR_H_

#include <string>

#include "net_common.h"

namespace huoguo {
namespace net {

class InetAddr {
public:
    // Late Bind
    explicit InetAddr();
    // default 
    explicit InetAddr(uint16_t port, const std::string &ip = "0.0.0.0", bool udp = false, bool loopback = false, bool ipv6 = false);

    // from sockaddr
    explicit InetAddr(const struct sockaddr_in& addr4);
    explicit InetAddr(const struct sockaddr_in6& addr6);

    int from_inet_addr4(const struct sockaddr_in& addr4);
    int from_inet_addr6(const struct sockaddr_in6& addr6);

    static InetAddr get_local_addr(int fd, bool ipv6 = false);
    static InetAddr get_remote_addr(int fd, bool ipv6 = false);
    // const struct sockaddr *get_sock_addr() const;
    const sockaddr *get_addr() const;
    socklen_t get_len() const;

    sa_family_t get_family() const;
    int get_type() const;
    int get_protocol() const;

    std::string get_ip() const;
    int get_port() const;
    
private:
    int m_addr_type;
    int m_addr_protocol;
    int m_addr_port;
    std::string m_addr_ip;
    sa_family_t m_addr_family;
    
    union {
        struct sockaddr_in  m_addr_v4;
        struct sockaddr_in6 m_addr_v6;
    };
};

} // namespace huoguo
} // namespace net

#endif // HUOGUO_NET_INET_ADDR_H_