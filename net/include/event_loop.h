#ifndef HUOGUO_NET_EVENT_LOOP_H_
#define HUOGUO_NET_EVENT_LOOP_H_

#include <atomic>
#include <memory>
#include "noncopyable.h"

namespace huoguo {
namespace net {

class Poller;
class EventLoop: public huoguo::utils::Noncopyable {
public:
    EventLoop();
    ~EventLoop();
    int run();
private:
    std::atomic<bool> m_stop;
    std::unique_ptr<Poller> m_poller;
};

} // namespace net
} // namespace huoguo

#endif // HUOGUO_NET_EVENT_LOOP_H_