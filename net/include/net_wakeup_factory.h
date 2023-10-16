#ifndef HUOGUO_NET_WAKEUPFACTORY_H_
#define HUOGUO_NET_WAKEUPFACTORY_H_

#include "net_wakeup_eventfd.h"
#include "net_wakeup_pipe.h"
#include "net_wakeup_sockpair.h"

namespace huoguo {
namespace net {

class WakeupFactory {
public:
    static EventIO *NewWakeup() {
    #if   defined (USE_EVENTFD_WAKEUP)
        return new EventfdWakeup;
    #elif defined (USE_PIPE_WAKEUP)
        return new PipeWakeup;
    #elif defined (USE_SOCKPAIR_WAKEUP)
        return new SockPairWakeup;
    #else
        return nullptr;
    #endif
    }
};

} // namespace net
} // namespace huoguo

#endif // HUOGUO_NET_WAKEUP_FACTORY_H_