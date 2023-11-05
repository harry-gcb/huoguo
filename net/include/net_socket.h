#ifndef HUOGUO_NET_SOCKET_H_
#define HUOGUO_NET_SOCKET_H_

#include <memory>
#include "utils_noncopyable.h"
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
    std::shared_ptr<Socket> accept(struct sockaddr *addr, socklen_t *addrlen);

    int connect(const InetAddr &addr);
    int connect(const struct sockaddr *addr, socklen_t addrlen);
    // TCP I/O
    virtual int read(uint8_t *data, size_t size) override;
    virtual int write(const uint8_t *data, size_t size) override;
    // UDP I/O
    int recvfrom(uint8_t *data, size_t size, InetAddr &addr);
    int sendto(const uint8_t *data, size_t size, const InetAddr &addr);

    int set_reuse_addr(bool reuse);
    int set_reuse_port(bool reuse);
    
    virtual int get_fd() override;
    virtual Channel *get_channel() override;
    virtual void set_channel(Channel *) override;

    const InetAddr &get_addr() const;
private:
    sa_family_t m_family;
    int m_fd;
    Channel *m_channel;
    InetAddr m_addr;
    
};

} // namespace net
} // namespace huoguo

#endif // HUOGUO_NET_SOCKET_H_