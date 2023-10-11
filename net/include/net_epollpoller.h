#ifdef NET_LINUX
#ifndef HUOGUO_NET_EPOLLPOLLER_H_
#define HUOGUO_NET_EPOLLPOLLER_H_

#include <list>
#include "poller.h"
#include "noncopyable.h"

namespace huoguo {
namespace net {

class EventIO;
class IOEvent;
class EPollPoller: public Poller, public huoguo::utils::Noncopyable {
public:
    EPollPoller();
    ~EPollPoller();
    virtual int add_event(std::shared_ptr<EventIO> event, bool enable_read, bool enable_write) override;
    virtual int set_event(std::shared_ptr<EventIO> event, bool enable_read, bool enable_write) override;
    virtual int del_event(std::shared_ptr<EventIO> event) override;
    virtual int get_event(std::list<std::shared_ptr<IOEvent> > &ioevents, int timeout) override;
private:
    int m_epoll_fd;
};

}
}

#endif // HUOGUO_NET_EPOLL_POLLER_H_
#endif