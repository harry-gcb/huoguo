#ifndef HUOGUO_NET_CHANNEL_H_
#define HUOGUO_NET_CHANNEL_H_

#include <memory>
#include <functional>
#include "socket.h"

namespace huoguo {
namespace net {

class EventLoop;
class Channel: public std::enable_shared_from_this<Channel> {
    using EventCallback = std::function<void()>;
public:
    Channel(EventLoop *loop, std::shared_ptr<EventIO> sock);
    ~Channel();
    std::string get_channel_id() const;
    std::shared_ptr<EventIO> get_event();
    void set_read_callback(EventCallback callback);
    void set_write_callback(EventCallback callback);
    void set_close_callback(EventCallback callback);
    void set_error_callback(EventCallback callback);

    void handle_read_event();
    void handle_write_event();
    void handle_close_event();
    void handle_error_event();

    void enable_read(bool enable);
    void enable_write(bool enable);
    void enable_all(bool enable);

    bool is_reading();
    bool is_writing();
private:
    EventLoop *m_loop;
    std::shared_ptr<EventIO> m_event;
    EventCallback m_read_callback;
    EventCallback m_write_callback;
    EventCallback m_close_callback;
    EventCallback m_error_callback;
    bool m_enable_read;
    bool m_enable_write;
    std::string m_channel_id;
};

} // namespace net
} // namespace huoguo

#endif // HUOGUO_NET_CHANNEL_H_