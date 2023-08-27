#ifndef HUOGUO_NET_SOCKET_H_
#define HUOGUO_NET_SOCKET_H_

#include <memory>
#include "inet_addr.h"

namespace huoguo {
namespace net {

class Channel;
class Socket {
public:
    Socket(sa_family_t family, int type, int protocol);
    Socket(int sock);
    Socket(){}
    ~Socket();

    int bind(const InetAddr &addr);
    int listen(int backlog = SOMAXCONN);
    std::shared_ptr<Socket> accept();

    int connect(const struct sockaddr *addr, socklen_t addrlen);

    int read(void *data, int len);
    int write(const void *data, int len);

    int set_reuse_addr(bool reuse);
    int set_reuse_port(bool reuse);
    
    int get_handle();
    Channel *get_channel();
    void set_channel(Channel *);
private:
    std::shared_ptr<Socket> accept(struct sockaddr *addr, socklen_t *addrlen);
private:
    sa_family_t m_family;
    int m_socket;
    Channel *m_channel;
    
};

} // namespace net
} // namespace huoguo

#endif // HUOGUO_NET_SOCKET_H_