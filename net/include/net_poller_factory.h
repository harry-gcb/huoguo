#ifndef HUOGUO_NET_POLLERFACTORY_H_
#define HUOGUO_NET_POLLERFACTORY_H_

#include "net_poller_epoll.h"
#include "net_poller_kqueue.h"
#include "net_poller_select.h"

namespace huoguo {
namespace net {

class PollerFactory {
public:
    static Poller *NewPoller() {
    #if defined (USE_EPOLL_POLLER)
        return new EPollPoller;
    #elif defined (USE_KQUEUE_POLLER)
        return new KQueuePoller;
    #elif defined (USE_SELECT_POLLER)
        return new SelectPoller;
    #else
        return nullptr;
    #endif
    }
};

} // namespace net
} // namespace huoguo

#endif // HUOGUO_NET_POLLER_FACTORY_H_