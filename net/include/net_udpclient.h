#ifndef HUOGUO_NET_UDPCLIENT_H_
#define HUOGUO_NET_UDPCLIENT_H_

#include "net_eventloop.h"
#include "net_inetaddr.h"
#include "net_udpconnection.h"

namespace huoguo {
namespace net {

class UdpClient {
public:
    UdpClient(EventLoop *loop, const InetAddr &addr, const std::string &name);
    ~UdpClient();

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

#endif // HUOGUO_NET_UDP_CLIENT_H_