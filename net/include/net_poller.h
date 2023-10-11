#ifndef HUOGUO_NET_POLLER_H_
#define HUOGUO_NET_POLLER_H_

#include <memory>
#include <list>

namespace huoguo {
namespace net {

class EventIO;
class IOEvent;
class Poller {
public:
    Poller() = default;
    virtual ~Poller() = default;
    virtual int add_event(std::shared_ptr<EventIO> event, bool enable_read, bool enable_write) = 0;
    virtual int set_event(std::shared_ptr<EventIO> event, bool enable_read, bool enable_write) = 0;
    virtual int del_event(std::shared_ptr<EventIO> event) = 0;
    virtual int get_event(std::list<std::shared_ptr<IOEvent> > &ioevents, int timeout_ms) = 0;
private:
};

}
}

#endif // HUOGUO_NET_POLLER_EVENT_H_