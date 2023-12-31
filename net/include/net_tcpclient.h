#ifndef HUOGUO_NET_TCPCLIENT_H_
#define HUOGUO_NET_TCPCLIENT_H_

// #include "utils.h"
#include "net_inetaddr.h"
#include "net_callback.h"
#include "net_connector.h"

namespace huoguo {
namespace net {

class EventLoop;
class TcpClient: huoguo::utils::Noncopyable {
public:
    TcpClient(EventLoop *loop, const InetAddr &addr, const std::string &name);
    void start();

    void set_connect_callback(const ConnectCallback &cb);
    void set_message_callback(const SegmentCallback &cb);
private:
    void add_connection(std::shared_ptr<Socket> sock);
    void del_connection(std::shared_ptr<TcpConnection> conn);
private:
    EventLoop *m_loop;
    std::unique_ptr<Connector> m_connector;
    InetAddr m_client_addr;
    std::string m_client_name;
    uint64_t m_conn_id;
    ConnectCallback m_connect_callback;
    SegmentCallback m_message_callback;
    std::shared_ptr<TcpConnection> m_connection;
};

} // namespace net
} // namespace huoguo

#endif // HUOGUO_NET_TCP_CLENT_H_