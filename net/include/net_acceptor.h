#ifndef HUOGUO_NET_ACCEPTOR_H_
#define HUOGUO_NET_ACCEPTOR_H_

#include <memory>
#include <functional>
#include "utils.h"
#include "net_inetaddr.h"


namespace huoguo {
namespace net {

class EventLoop;
class Channel;
class Socket;
class Acceptor: huoguo::utils::Noncopyable {
    using EstablishCallback = std::function<void(std::shared_ptr<Socket>)>;
public:
    Acceptor(EventLoop *loop, const InetAddr &addr, bool reuse);
    ~Acceptor();

    void set_establish_callback(EstablishCallback callback);

    void listen();
private:
    void handle_read_event();
private:
    EventLoop *m_loop;
    bool m_listening;
    std::shared_ptr<Socket> m_socket;
    std::shared_ptr<Channel> m_channel;
    EstablishCallback m_establish_callback;
};

} // namespace huoguo
} // namespace net

#endif // HUOGUO_NET_ACCEPTOR_H_