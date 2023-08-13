#ifndef HUOGUO_NET_TCP_SERVER_H_
#define HUOGUO_NET_TCP_SERVER_H_

#include <memory>
#include "callback.h"
#include "noncopyable.h"
#include "inet_addr.h"
#include "acceptor.h"

namespace huoguo {
namespace net {

class EventLoop;
class Acceptor;

class TcpServer: huoguo::utils::Noncopyable {
public:
    TcpServer(EventLoop *loop, const InetAddr &addr, const std::string &name, bool reuse = true);
    void start();

    void set_connect_callback(const ConnectCallback &cb);
    void set_message_callback(const MessageCallback &cb);
private:
    EventLoop *m_loop;
    std::unique_ptr<Acceptor> m_acceptor;

    ConnectCallback m_connect_callback;
    MessageCallback m_message_callback;
};

} // namespace net
} // namespace huoguo

#endif // HUOGUO_NET_TCP_SERVER_H