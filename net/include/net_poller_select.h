#ifdef USE_SELECT_POLLER
#ifndef HUOGUO_NET_SELECTPOLLER_H_
#define HUOGUO_NET_SELECTPOLLER_H_

#include <list>
#include "utils.h"
#include "net_poller.h"

namespace huoguo {
namespace net {

class EventIO;
class IOEvent;
class SelectPoller: public Poller, public huoguo::utils::Noncopyable {
    class EventFd {
    public:
        int m_fd = -1;
        void *m_user_data = nullptr;
        bool m_enable_read = false;
        bool m_enable_write = false;
        bool m_enable_error=  false;

        EventFd(): m_fd(-1), m_user_data(nullptr), m_enable_read(false), m_enable_write(false), m_enable_error(false) {}
        EventFd(int fd, void *user_data, bool enable_read, bool enable_write, bool enable_error = false)
            : m_fd(fd), m_user_data(user_data), m_enable_read(enable_read), m_enable_write(enable_write), m_enable_error(enable_error) {}
    };
public:
    SelectPoller();
    ~SelectPoller();
    virtual int add_event(std::shared_ptr<EventIO> event, bool enable_read, bool enable_write) override;
    virtual int set_event(std::shared_ptr<EventIO> event, bool enable_read, bool enable_write) override;
    virtual int del_event(std::shared_ptr<EventIO> event) override;
    virtual int get_event(std::list<std::shared_ptr<IOEvent> > &ioevents, int timeout) override;
private:
    std::list<EventFd> m_eventfds;
};

} // namespace net
} // namespace huoguo

#endif // HUOGUO_NET_SELECTPOLLER_H_
#endif