#include "utils_logger.h"
#include "net_callback.h"
#include "net_tcpconnection.h"

namespace huoguo {
namespace net {

void default_connect_callback(const std::shared_ptr<TcpConnection> conn) {
    InfoL("[%s] %s:%d->%s:%d is %s", conn->get_trace_id().c_str(),
                                    conn->get_remote_ip().c_str(), conn->get_remote_port(),
                                    conn->get_local_ip().c_str(), conn->get_local_port(),
                                    conn->is_connected() ? "UP" : "DOWN");
}

void default_message_callback(const std::shared_ptr<TcpConnection> conn, const uint8_t *data, size_t size) {
    InfoL("[%s] %s:%d->%s:%d send %d bytes", conn->get_trace_id().c_str(),
                                    conn->get_remote_ip().c_str(), conn->get_remote_port(),
                                    conn->get_local_ip().c_str(), conn->get_local_port(),
                                    size);
}


}
}