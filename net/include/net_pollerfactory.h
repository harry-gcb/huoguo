#ifndef HUOGUO_NET_POLLERFACTORY_H_
#define HUOGUO_NET_POLLERFACTORY_H_

#include "net_epollpoller.h"
#include "net_kqueuepoller.h"

namespace huoguo {
namespace net {

class PollerFactory {
public:
    static Poller *NewPoller() {
    #if defined (NET_LINUX)
        return new EPollPoller;
    #elif defined (NET_MACOS)
        return new KQueuePoller;
    #else
        return nullptr;
    #endif
    }
};

} // namespace net
} // namespace huoguo

#endif // HUOGUO_NET_POLLER_FACTORY_H_