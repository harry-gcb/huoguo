#include "event_loop.h"
#include "logger.h"

namespace huoguo {
namespace net {

EventLoop::EventLoop()
    : m_stop(false) {

}

EventLoop::~EventLoop() {

}

int EventLoop::run() {
    INFO("EventLoop start running");
    while (!m_stop) {
        
    }
    INFO("EventLoop exit running");
    return 0;
}

} // namespace net
} // namespace huoguo