#ifdef USE_EVENTFD_WAKEUP
#ifndef HUOGUO_NET_EVENTFDWAKEUP_H_
#define HUOGUO_NET_EVENTFDWAKEUP_H_

#include <memory>
#include "net_eventio.h"

namespace huoguo {
namespace net {

class Socket;
class EventfdWakeup: public EventIO {
public:
    EventfdWakeup();
    // ~EventfdWakeup();

    virtual int get_fd() override;
    virtual Channel *get_channel() override;
    virtual void set_channel(Channel *channel) override;
    virtual int read(uint8_t *data, size_t size) override;
    virtual int write(const uint8_t *data, size_t size) override;
private:
    std::shared_ptr<Socket> m_event_fd;
};

}
}

#endif // HUOGUO_NET_EVENTFD_WAKEUP_H_
#endif