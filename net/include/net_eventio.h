#ifndef HUOGUO_NET_EVENTIO_H_
#define HUOGUO_NET_EVENTIO_H_

namespace huoguo {
namespace net {

class Channel;
class EventIO {
public:
    virtual ~EventIO() {}
    virtual int get_fd() = 0;
    virtual Channel *get_channel() = 0;
    virtual void set_channel(Channel *channel) = 0;
    virtual int read(uint8_t *data, size_t size) = 0;
    virtual int write(const uint8_t *data, size_t size) = 0;
};

} // namespace net
} // namespace huoguo

#endif // HUOGUO_NET_EVENT_IO_H_