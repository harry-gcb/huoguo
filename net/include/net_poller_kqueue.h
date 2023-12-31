#ifdef USE_KQUEUE_POLLER
#ifndef HUOGUO_NETKQUEUE_H_
#define HUOGUO_NETKQUEUE_H_

#include <list>
#include "net_poller.h"
#include "noncopyable.h"

namespace huoguo {
namespace net {

class EventIO;
class IOEvent;
class KQueuePoller: public Poller, public huoguo::utils::Noncopyable {
public:
    KQueuePoller();
    ~KQueuePoller();
    virtual int add_event(std::shared_ptr<EventIO> event, bool enable_read, bool enable_write) override;
    virtual int set_event(std::shared_ptr<EventIO> event, bool enable_read, bool enable_write) override;
    virtual int del_event(std::shared_ptr<EventIO> event) override;
    virtual int get_event(std::list<std::shared_ptr<IOEvent> > &ioevents, int timeout) override;
private:
    int m_kqueue_fd;
};
 
}
}
#endif // HUOGUO_NET_KQUEUE_H_
#endif