#ifndef HUOGUO_NET_TCP_CLIENT_H_
#define HUOGUO_NET_TCP_CLIENT_H_

#include "inet_addr.h"
#include "noncopyable.h"
#include "callback.h"
#include "connector.h"

namespace huoguo {
namespace net {

class EventLoop;
class TcpClient: huoguo::utils::Noncopyable {
public:
    TcpClient(EventLoop *loop, const InetAddr &addr, const std::string &name);
    void start();

    void set_connect_callback(const ConnectCallback &cb);
    void set_message_callback(const MessageCallback &cb);
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
    MessageCallback m_message_callback;
    std::shared_ptr<TcpConnection> m_connection;
};

} // namespace net
} // namespace huoguo

#endif // HUOGUO_NET_TCP_CLENT_H_