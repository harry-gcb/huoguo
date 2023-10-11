#ifndef HUOGUO_NET_SOCKET_H_
#define HUOGUO_NET_SOCKET_H_

#include <memory>
#include "utils.h"
#include "net_inetaddr.h"
#include "net_eventio.h"

namespace huoguo {
namespace net {

class Channel;
class Socket: public EventIO, huoguo::utils::Noncopyable {
public:
    Socket(sa_family_t family, int type, int protocol);
    Socket(int sock);
    ~Socket();

    int bind(const InetAddr &addr);
    int listen(int backlog = SOMAXCONN);
    std::shared_ptr<Socket> accept();

    int connect(const struct sockaddr *addr, socklen_t addrlen);
    // TCP I/O
    virtual int read(char *data, int len) override;
    virtual int write(const char *data, int len) override;
    // UDP I/O
    int recvfrom(char *data, int len, InetAddr &addr);
    int sendto(const char *data, int len, const InetAddr &addr);

    int set_reuse_addr(bool reuse);
    int set_reuse_port(bool reuse);
    
    virtual int get_fd() override;
    virtual Channel *get_channel() override;
    virtual void set_channel(Channel *) override;
private:
    std::shared_ptr<Socket> accept(struct sockaddr *addr, socklen_t *addrlen);
private:
    sa_family_t m_family;
    int m_fd;
    Channel *m_channel;
    
};

} // namespace net
} // namespace huoguo

#endif // HUOGUO_NET_SOCKET_H_