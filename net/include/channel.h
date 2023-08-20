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
    Channel(EventLoop *loop, std::shared_ptr<Socket> sock);
    std::shared_ptr<Socket> get_socket();
    void set_read_callback(EventCallback callback);
    void set_write_callback(EventCallback callback);
    void set_close_callback(EventCallback callback);
    void set_error_callback(EventCallback callback);
    void handle_read_event();
    void handle_write_event();
    void handle_close_event();
    void handle_error_event();
    void enable_read_event();
    void disable_read_event();
    void enable_write_event();
    void disable_write_event();
    bool enable_read();
    bool enable_write();
private:
    EventLoop *m_loop;
    std::shared_ptr<Socket> m_socket;
    EventCallback m_read_callback;
    EventCallback m_write_callback;
    EventCallback m_close_callback;
    EventCallback m_error_callback;
    bool m_enable_read;
    bool m_enable_write;
};

} // namespace net
} // namespace huoguo

#endif // HUOGUO_NET_CHANNEL_H_