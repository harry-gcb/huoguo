#ifndef HUOGUO_NET_SOCKET_H_
#define HUOGUO_NET_SOCKET_H_

#include <memory>
#include "inet_addr.h"

namespace huoguo {
namespace net {

class IOEvent;
class Socket {
public:
    Socket(std::shared_ptr<IOEvent> event);
    Socket(std::shared_ptr<IOEvent> event, bool is_ipv4 = true, bool is_tcp = true);
    ~Socket();
    
    int bind(const InetAddr &addr);
    int get_handle();
private:
    std::weak_ptr<IOEvent> m_event;
    int m_socket;
};

} // namespace net
} // namespace huoguo

#endif // HUOGUO_NET_SOCKET_H_