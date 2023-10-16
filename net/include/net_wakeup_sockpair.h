#ifdef USE_SOCKPAIR_WAKEUP
#ifndef HUOGUO_NET_SOCKPAIRWAKEUP_H_
#define HUOGUO_NET_SOCKPAIRWAKEUP_H_

#include <memory>
#include "net_eventio.h"

namespace huoguo {
namespace net {

class Socket;
class SockPairWakeup: public EventIO {
public:
    SockPairWakeup();
    // ~EventfdWakeup();

    virtual int get_fd() override;
    virtual Channel *get_channel() override;
    virtual void set_channel(Channel *channel) override;
    virtual int read(char *data, int len) override;
    virtual int write(const char *data, int len) override;
private:
    std::mutex m_accept_mutex;
    std::thread m_accept_thread;
    std::condition_variable m_accetp_cv;
    bool m_accept_start;
    std::shared_ptr<Socket> m_acceptor;
    std::shared_ptr<Socket> m_connector;
    std::shared_ptr<Socket> m_reader;
};

} // namespace net
} // namespace huoguo

#endif // HUOGUO_NET_SOCKPAIRWAKEUP_H_
#endif