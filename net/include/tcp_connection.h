#ifndef HUOGUO_NET_TCP_CONNECTION_H_
#define HUOGUO_NET_TCP_CONNECTION_H_

#include <string>
#include <memory>
#include "inet_addr.h"
#include "noncopyable.h"
#include "callback.h"

namespace huoguo {
namespace net {

#define BUF_SIZE 4096
class Channel;
class Socket;
class EventLoop;
class TcpConnection: public huoguo::utils::Noncopyable, public std::enable_shared_from_this<TcpConnection> {
public:
    TcpConnection(EventLoop *loop, std::shared_ptr<Socket> sock, const InetAddr &local_addr, const InetAddr &peer_addr);
    ~TcpConnection();

    void establish();
    void shutdown();
    void set_connect_callback(ConnectCallback callback);
    void set_message_callback(MessageCallback callback);
    void set_close_callback(CloseCallback callback);

    int send(const std::string &buffer);

    std::string get_trace_id() const;
    std::string get_local_ip() const;
    int get_local_port() const;
    std::string get_remote_ip() const;
    int get_remote_port() const;

    bool is_connected();
private:
    void handle_read_event();
    void handle_write_event();
    void handle_close_event();
    void handle_error_event();
private:
    EventLoop *m_loop;
    std::shared_ptr<Socket> m_socket;
    std::shared_ptr<Channel> m_channel;
    const InetAddr m_local_addr;
    const InetAddr m_remote_addr;
    bool m_connected;
    uint8_t m_buffer[BUF_SIZE];
    ConnectCallback m_connect_callback;
    MessageCallback m_message_callback;
    CloseCallback m_close_callback;
    std::string m_trace_id;
};

} // namespace net
} // namespace huoguo

#endif // HUOGUO_NET_TCP_CONNECTION_H_