#ifndef HUOGUO_NET_UDPSERVER_H_
#define HUOGUO_NET_UDPSERVER_H_

#include "net_eventloop.h"
#include "net_inetaddr.h"
#include "net_udpconnection.h"
#include "net_callback.h"

namespace huoguo {
namespace net {

class UdpServer {
public:
    UdpServer() {};
    UdpServer(EventLoop *loop, const InetAddr &addr, const std::string &name, bool reuse = true);
    ~UdpServer();

    void set_message_callback(DatagramCallback callback);
    void start();

    int sendto(const InetAddr &addr, const std::string &buffer);
    int sendto(const InetAddr &addr, const uint8_t *data, size_t size);
private:
    EventLoop *m_loop;
    std::shared_ptr<UdpConnection> m_connection;
    std::string m_trace_id;
    InetAddr m_inet_addr;
};

} // namespace net
} // namespace huoguo

#endif // HUOGUO_NET_UDP_SERVER_H_