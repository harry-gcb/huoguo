#ifndef HUOGUO_NET_UDP_CLIENT_H_
#define HUOGUO_NET_UDP_CLIENT_H_

#include "event_loop.h"
#include "inet_addr.h"

namespace huoguo {
namespace net {

class UdpClient {
public:
    UdpClient(EventLoop *loop, const InetAddr &addr, const std::string &name);
private:
    EventLoop *m_loop;
};

} // namespace net
} // namespace huoguo

#endif // HUOGUO_NET_UDP_CLIENT_H_