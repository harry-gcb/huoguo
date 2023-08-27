#ifndef HUOGUO_NET_WAKEUP_FACTORY_H_
#define HUOGUO_NET_WAKEUP_FACTORY_H_

#include "eventfd_wakeup.h"
#include "pipe2_wakeup.h"

namespace huoguo {
namespace net {

class WakeupFactory {
public:
    static EventIO *NewWakeup() {
    #ifdef USE_EPOLL
        return new EventfdWakeup;
    #elif defined (USE_KQUEUE)
        return new Pipe2Wakeup;
    #endif
    }
};

} // namespace net
} // namespace huoguo

#endif // HUOGUO_NET_WAKEUP_FACTORY_H_