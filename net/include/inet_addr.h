#ifndef HUOGUO_NET_INET_ADDR_H_
#define HUOGUO_NET_INET_ADDR_H_

#include <string>
#include <netinet/in.h>

namespace huoguo {
namespace net {

class InetAddr {
public:
    explicit InetAddr(uint16_t port, bool loopback = false, bool ipv6 = false);
    // const struct sockaddr *get_sock_addr() const;
    std::string get_addr();
    int get_port();
    
private:
    union {
        struct sockaddr_in  addr4;
        struct sockaddr_in6 addr6;
    };
};

} // namespace huoguo
} // namespace net

#endif // HUOGUO_NET_INET_ADDR_H_