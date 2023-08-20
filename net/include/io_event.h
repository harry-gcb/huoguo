#ifndef HUOGUO_NET_IO_EVENT_H_
#define HUOGUO_NET_IO_EVENT_H_

namespace huoguo {
namespace net {

class Channel;
class IOEvent {
public:
    bool m_read_occurred;
    bool m_write_occurred;
    bool m_error_occurred;
    Channel *m_channel;
};

} // namespace net
} // namespace huoguo


#endif // HUOGUO_NET_IO_EVENT_H_