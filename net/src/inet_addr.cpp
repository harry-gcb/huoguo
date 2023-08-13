#include "inet_addr.h"
#include <cstring>
#include <netinet/in.h>
#include <arpa/inet.h>

namespace huoguo {
namespace net {

static const int addr_len = 128;

InetAddr::InetAddr(uint16_t port, bool loopback, bool ipv6) {
    if (ipv6) {
        memset(&addr6, 0, sizeof(addr6));
        addr6.sin6_family = AF_INET6;
        addr6.sin6_addr = loopback ? in6addr_loopback : in6addr_any;
        addr6.sin6_port = htobe16(port);
    } else {
        memset(&addr4, 0, sizeof(addr4));
        addr4.sin_family = AF_INET;
        addr4.sin_addr.s_addr = loopback ? INADDR_LOOPBACK : INADDR_ANY;
        addr4.sin_port = htobe16(port);
    }
}

std::string InetAddr::get_addr() {
    char addr[addr_len] = { 0 };
    if (AF_INET == addr4.sin_family) {
        inet_ntop(AF_INET, &addr4.sin_addr, addr, static_cast<socklen_t>(addr_len));
    } else {
        inet_ntop(AF_INET6, &addr6.sin6_addr, addr, static_cast<socklen_t>(addr_len));
    }
    return addr;
}
int InetAddr::get_port() {
    if (AF_INET == addr4.sin_family) {
        return addr4.sin_port;
    } else {
        return addr6.sin6_port;
    }
}

} // namespace huoguo
} // namespace net