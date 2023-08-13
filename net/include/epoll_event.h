#ifndef HUOGUO_NET_EPOLL_POLLER_H_
#define HUOGUO_NET_EPOLL_POLLER_H_

#include <list>
#include "poller.h"

namespace huoguo {
namespace net {

class Socket;
class IOEvent;
class EPollPoller: public Poller {
public:
    virtual int addEvent(std::shared_ptr<Socket> sock, bool enable_read, bool enable_write) override;
    virtual int setEvent(std::shared_ptr<Socket> sock, bool enable_read, bool enable_write) override;
    virtual int delEvent(std::shared_ptr<Socket> sock) override;
    virtual int getEvent(std::list<std::shared_ptr<IOEvent> &events, int timeouts) override;
private:
    int m_epoll_fd;
};

}
}

#endif // HUOGUO_NET_EPOLL_POLLER_H_