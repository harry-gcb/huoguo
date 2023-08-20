#ifndef HUOGUO_NET_POLLER_FACTORY_H_
#define HUOGUO_NET_POLLER_FACTORY_H_

namespace huoguo {
namespace net {

class Poller;
class EventLoop;
class PollerFactory {
public:
    static Poller *NewPoller(EventLoop *loop = nullptr);
};

} // namespace net
} // namespace huoguo

#endif // HUOGUO_NET_POLLER_FACTORY_H_