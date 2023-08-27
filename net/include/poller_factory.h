#ifndef HUOGUO_NET_POLLER_FACTORY_H_
#define HUOGUO_NET_POLLER_FACTORY_H_

#include "epoll_poller.h"
#include "kqueue_poller.h"

namespace huoguo {
namespace net {

class PollerFactory {
public:
    static Poller *NewPoller() {
    #ifdef USE_EPOLL
        return new EPollPoller;
    #elif defined (USE_KQUEUE)
        return new KQueuePoller;
    #endif
    }
};

} // namespace net
} // namespace huoguo

#endif // HUOGUO_NET_POLLER_FACTORY_H_