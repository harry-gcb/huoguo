#ifndef HUOGUO_NET_TCP_SERVER_H_
#define HUOGUO_NET_TCP_SERVER_H_

#include <memory>
#include <map>
#include "callback.h"
#include "noncopyable.h"
#include "inet_addr.h"
#include "acceptor.h"

namespace huoguo {
namespace net {

class EventLoop;
class Acceptor;
class Socket;
class TcpServer: huoguo::utils::Noncopyable {
public:
    TcpServer(EventLoop *loop, const InetAddr &addr, const std::string &name, bool reuse = true);
    ~TcpServer();
    void start();

    void set_connect_callback(const ConnectCallback &cb);
    void set_message_callback(const MessageCallback &cb);
private:
    void add_connection(std::shared_ptr<Socket> sock);
    void del_connection(TcpConnectionPtr conn);
private:
    EventLoop *m_loop;
    std::unique_ptr<Acceptor> m_acceptor;
    InetAddr m_server_addr;
    std::string m_server_name;
    uint64_t m_conn_id;
    ConnectCallback m_connect_callback;
    MessageCallback m_message_callback;
    std::map<std::string, TcpConnectionPtr> m_connections;
};

} // namespace net
} // namespace huoguo

#endif // HUOGUO_NET_TCP_SERVER_H