#ifdef USE_KQUEUE
#ifndef HUOGUO_NET_KQUEUE_H_
#define HUOGUO_NET_KQUEUE_H_

#include <list>
#include "poller.h"
#include "noncopyable.h"

namespace huoguo {
namespace net {

class Socket;
class IOEvent;
class KQueuePoller: public Poller, public huoguo::utils::Noncopyable {
public:
    KQueuePoller();
    ~KQueuePoller();
    virtual int add_event(std::shared_ptr<Socket> sock, bool enable_read, bool enable_write) override;
    virtual int set_event(std::shared_ptr<Socket> sock, bool enable_read, bool enable_write) override;
    virtual int del_event(std::shared_ptr<Socket> sock) override;
    virtual int get_event(std::list<std::shared_ptr<IOEvent> > &ioevents, int timeout) override;
private:
    int m_kqueue_fd;
};
 
}
}
#endif // HUOGUO_NET_KQUEUE_H_
#endif