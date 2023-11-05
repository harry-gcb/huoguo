#ifndef HUOGUO_NET_EVENTLOOP_H_
#define HUOGUO_NET_EVENTLOOP_H_

#include <atomic>
#include <memory>
#include <map>
#include <list>
#include <functional>
#include "utils_noncopyable.h"

namespace huoguo {
namespace net {

class Poller;
class EventIO;
class Channel;
class EventLoop: public huoguo::utils::Noncopyable {
    using Callback = std::function<void()>;
public:
    EventLoop();
    ~EventLoop();
    int run();
    void stop();

    int add_channel(std::shared_ptr<Channel> channel);
    int set_channel(std::shared_ptr<Channel> channel);
    int del_channel(std::shared_ptr<Channel> channel);

    void handle_read_event();
    void active_read_event();
    void push_close_event(Callback callback);
    void handle_close_event();
    
private:
    std::atomic<bool> m_stop;
    std::unique_ptr<Poller> m_poller;
    std::shared_ptr<EventIO> m_event_io;
    std::shared_ptr<Channel> m_channel;
    std::list<Callback> m_callback;
};

} // namespace net
} // namespace huoguo

#endif // HUOGUO_NET_EVENT_LOOP_H_