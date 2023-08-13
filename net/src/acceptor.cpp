#include "acceptor.h"
#include "event_loop.h"

namespace huoguo {
namespace net {

Acceptor::Acceptor(EventLoop *loop, const InetAddr &addr, bool reuse)
    : m_loop(loop) {

}

Acceptor::~Acceptor() {

}

}
}