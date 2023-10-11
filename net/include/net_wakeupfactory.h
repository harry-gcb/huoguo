#ifndef HUOGUO_NET_WAKEUPFACTORY_H_
#define HUOGUO_NET_WAKEUPFACTORY_H_

#include "net_eventfdwakeup.h"
#include "net_pipewakeup.h"

namespace huoguo {
namespace net {

class WakeupFactory {
public:
    static EventIO *NewWakeup() {
    #if   defined (NET_LINUX)
        return new EventfdWakeup;
    #elif defined (NET_MACOS)
        return new PipeWakeup;
    #else
        return nullptr;
    #endif
    }
};

} // namespace net
} // namespace huoguo

#endif // HUOGUO_NET_WAKEUP_FACTORY_H_