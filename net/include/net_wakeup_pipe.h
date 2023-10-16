#ifdef USE_PIPE_WAKEUP
#ifndef HUOGUO_NET_PIPEWAKEUP_H_
#define HUOGUO_NET_PIPEWAKEUP_H_

#include <memory>
#include "net_eventio.h"

namespace huoguo {
namespace net {

class Socket;
class Channel;
class PipeWakeup: public EventIO {
public:
    PipeWakeup();

    virtual int get_fd() override;
    virtual Channel *get_channel() override;
    virtual void set_channel(Channel *channel) override;
    virtual int read(void *data, int len) override;
    virtual int write(const void *data, int len) override;
private:
    std::shared_ptr<Socket> m_pipe_0;
    std::shared_ptr<Socket> m_pipe_1;
};

} // namespace net
} // namespace huoguo

#endif // HUOGUO_NET_PIPE_WAKEUP_H_
#endif