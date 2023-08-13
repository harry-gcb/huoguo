#ifndef HUOGUO_NET_POLLER_H_
#define HUOGUO_NET_POLLER_H_

#include <memory>

namespace huoguo {
namespace net {

class Poller {
public:
    virtual int addEvent(std::shared_ptr<Socket> sock, bool enable_read, bool enable_write) = 0;
    virtual int setEvent(std::shared_ptr<Socket> sock, bool enable_read, bool enable_write) = 0;
    virtual int delEvent(std::shared_ptr<Socket> sock) = 0;
    virtual int getEvent(std::list<std::shared_ptr<IOEvent> &events, int timeouts) = 0;
private:
};

}
}

#endif // HUOGUO_NET_POLLER_EVENT_H_