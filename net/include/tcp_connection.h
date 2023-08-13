#ifndef HUOGUO_NET_TCP_CONNECTION_H_
#define HUOGUO_NET_TCP_CONNECTION_H_

#include <string>

namespace huoguo {
namespace net {

class TcpConnection {
public:
    std::string get_conn_name() const;
    std::string get_remote_addr() const;
    int get_remote_port() const;
    std::string get_local_addr() const;
    int get_local_port() const;
    bool is_connected();
};

} // namespace net
} // namespace huoguo

#endif // HUOGUO_NET_TCP_CONNECTION_H_