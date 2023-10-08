#include "callback.h"
#include "logger.h"
#include "tcp_connection.h"

namespace huoguo {
namespace net {

void default_connect_callback(std::shared_ptr<TcpConnection> conn) {
    INFO("[%s] %s:%d->%s:%d is %s", conn->get_trace_id().c_str(),
                                    conn->get_remote_ip().c_str(), conn->get_remote_port(),
                                    conn->get_local_ip().c_str(), conn->get_local_port(),
                                    conn->is_connected() ? "UP" : "DOWN");
}

void default_message_callback(std::shared_ptr<TcpConnection> conn, const char *data, size_t len) {
    INFO("[%s] %s:%d->%s:%d send %d bytes", conn->get_trace_id().c_str(),
                                    conn->get_remote_ip().c_str(), conn->get_remote_port(),
                                    conn->get_local_ip().c_str(), conn->get_local_port(),
                                    len);
}


}
}