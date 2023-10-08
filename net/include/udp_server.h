#ifndef HUOGUO_NET_UDP_SERVER_H_
#define HUOGUO_NET_UDP_SERVER_H_

#include "event_loop.h"
#include "inet_addr.h"
#include "udp_connection.h"
#include "callback.h"

namespace huoguo {
namespace net {

class UdpServer {
public:
    UdpServer() {};
    UdpServer(EventLoop *loop, const InetAddr &addr, const std::string &name, bool reuse = true);
    ~UdpServer();

    void set_datagram_callback(DatagramCallback callback);
private:
    EventLoop *m_loop;
    std::shared_ptr<UdpConnection> m_connection;
    std::string m_trace_id;
    InetAddr m_inet_addr;
};

} // namespace net
} // namespace huoguo

#endif // HUOGUO_NET_UDP_SERVER_H_