#include "tcp_connection.h"

namespace huoguo {
namespace net {

std::string TcpConnection::get_conn_name() const {
    return "";
}
std::string TcpConnection::get_remote_addr() const {
    return "";
}
int TcpConnection::get_remote_port() const {
    return 0;
}
std::string TcpConnection::get_local_addr() const {
    return "";
}
int TcpConnection::get_local_port() const {
    return 0;
}

bool TcpConnection::is_connected() {
    return true;
}

} // namespace huoguo
} // namespace net