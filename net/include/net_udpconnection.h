#ifndef HUOGUO_NET_UDP_CONNECTION_H_
#define HUOGUO_NET_UDP_CONNECTION_H_

#include <string>
#include <memory>
#include "utils_noncopyable.h"
#include "net_callback.h"
#include "net_inetaddr.h"

namespace huoguo {
namespace net {

#define BUF_SIZE 4096
class Channel;
class Socket;
class EventLoop;
class UdpConnection: public huoguo::utils::Noncopyable, public std::enable_shared_from_this<UdpConnection> {
public:
    UdpConnection(EventLoop *loop, std::shared_ptr<Socket> sock);
    ~UdpConnection();

    void set_message_callback(DatagramCallback callback);

    int sendto(const InetAddr &addr, const std::string &buffer);
    int sendto(const InetAddr &addr, const uint8_t *data, size_t size);

    std::string get_trace_id() const;

    // std::string get_local_ip() const;
    // int get_local_port() const;
    // std::string get_remote_ip() const;
    // int get_remote_port() const;
private:
    void handle_read_event();
    void handle_error_event();
private:
    EventLoop *m_loop;
    std::shared_ptr<Socket> m_socket;
    std::shared_ptr<Channel> m_channel;
    std::string m_trace_id;
    uint8_t m_buffer[BUF_SIZE];
    DatagramCallback m_message_callback;
    
    InetAddr m_current_addr;

    InetAddr m_local_addr;
    InetAddr m_remote_addr;
};

} // namespace net
} // namespace huoguo

#endif // HUOGUO_NET_UDP_CONNECTION_H_