#ifndef HUOGUO_NET_EVENTFD_WAKEUP_H_
#define HUOGUO_NET_EVENTFD_WAKEUP_H_

#include <memory>
#include "event_io.h"

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
    virtual int read(void *data, int len) override;
    virtual int write(const void *data, int len) override;
private:
    std::shared_ptr<Socket> m_event_fd;
};

}
}

#endif // HUOGUO_NET_EVENTFD_WAKEUP_H_