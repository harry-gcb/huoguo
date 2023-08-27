#include "poller_factory.h"
#include "epoll_poller.h"
#include "kqueue_poller.h"
#include "event_loop.h"

namespace huoguo {
namespace net {

Poller *PollerFactory::NewPoller(EventLoop *loop) {
#ifdef USE_EPOLL
    return new EPollPoller;
#elif defined (USE_KQUEUE)
    return new KQueuePoller;
#endif

}

}
}