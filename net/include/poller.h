#ifndef HUOGUO_NET_POLLER_H_
#define HUOGUO_NET_POLLER_H_

#include <memory>
#include <list>
#include "io_event.h"

namespace huoguo {
namespace net {

class Socket;
class Poller {
public:
    Poller() = default;
    virtual ~Poller() = default;
    virtual int add_event(std::shared_ptr<Socket> sock, bool enable_read, bool enable_write) = 0;
    virtual int set_event(std::shared_ptr<Socket> sock, bool enable_read, bool enable_write) = 0;
    virtual int del_event(std::shared_ptr<Socket> sock) = 0;
    virtual int get_event(std::list<std::shared_ptr<IOEvent> > &ioevents, int timeout) = 0;
private:
};

}
}

#endif // HUOGUO_NET_POLLER_EVENT_H_