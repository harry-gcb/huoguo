#ifndef HUOGUO_NET_UDPCLIENT_H_
#define HUOGUO_NET_UDPCLIENT_H_

#include "net_eventloop.h"
#include "net_inetaddr.h"

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