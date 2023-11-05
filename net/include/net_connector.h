#ifndef HUOGUO_NET_CONNECTOR_H_
#define HUOGUO_NET_CONNECTOR_H_

#include <memory>
#include <functional>
#include "utils_noncopyable.h"
#include "net_inetaddr.h"

namespace huoguo {
namespace net {

class EventLoop;
class Channel;
class Socket;
class Connector: huoguo::utils::Noncopyable {
    using EstablishCallback = std::function<void(std::shared_ptr<Socket>)>;
public:
    Connector(EventLoop *loop, const InetAddr &addr);
    ~Connector();

    void set_establish_callback(EstablishCallback callback);

    void connect();
private:
    void handle_read_event();
private:
    EventLoop *m_loop;
    bool m_connecting;
    InetAddr m_addr;
    EstablishCallback m_establish_callback;
};

} // namespace net
} // namespace huoguo

#endif // HUOGUO_NET_CONNECTOR_H_