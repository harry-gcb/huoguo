#ifdef USE_EVENTFD_WAKEUP
#include "net_wakeup_eventfd.h"
#include "net_socket.h"
#include <sys/eventfd.h>

namespace huoguo {
namespace net {

EventfdWakeup::EventfdWakeup() 
    : m_event_fd(new Socket(::eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC))) {
}

int EventfdWakeup::get_fd() {
    return m_event_fd->get_fd();
}

Channel *EventfdWakeup::get_channel() {
    return m_event_fd->get_channel();
}

void EventfdWakeup::set_channel(Channel *channel) {
    m_event_fd->set_channel(channel);
}

int EventfdWakeup::read(char *data, int len) {
    return m_event_fd->read(data, len);
}

int EventfdWakeup::write(const char *data, int len) {
    return m_event_fd->write(data, len);
}

} // namespace net
} // namespace huoguo
#endif