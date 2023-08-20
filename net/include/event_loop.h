#ifndef HUOGUO_NET_EVENT_LOOP_H_
#define HUOGUO_NET_EVENT_LOOP_H_

#include <atomic>
#include <memory>
#include "noncopyable.h"

namespace huoguo {
namespace net {

class Poller;
class Channel;
class EventLoop: public huoguo::utils::Noncopyable {
public:
    EventLoop();
    ~EventLoop();
    int run();

    int add_channel(std::shared_ptr<Channel> channel);
    int set_channel(std::shared_ptr<Channel> channel);
    int del_channel(std::shared_ptr<Channel> channel);
private:
    std::atomic<bool> m_stop;
    std::unique_ptr<Poller> m_poller;
};

} // namespace net
} // namespace huoguo

#endif // HUOGUO_NET_EVENT_LOOP_H_