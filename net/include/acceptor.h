#ifndef HUOGUO_NET_ACCEPTOR_H_
#define HUOGUO_NET_ACCEPTOR_H_

#include "noncopyable.h"

namespace huoguo {
namespace net {

class EventLoop;
class InetAddr;

class Acceptor: huoguo::utils::Noncopyable {
public:
    Acceptor(EventLoop *loop, const InetAddr &addr, bool reuse);
    ~Acceptor();
private:
    EventLoop *m_loop;
};

} // namespace huoguo
} // namespace net

#endif // HUOGUO_NET_ACCEPTOR_H_