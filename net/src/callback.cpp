#include "callback.h"
#include "logger.h"
#include "tcp_connection.h"

namespace huoguo {
namespace net {

void default_connect_callback(const TcpConnectionPtr &conn) {
    INFO("[%s] %s:%d->%s:%d is %s", conn->get_name().c_str(),
                                    conn->get_remote_ip().c_str(), conn->get_remote_port(),
                                    conn->get_local_ip().c_str(), conn->get_local_port(),
                                    conn->is_connected() ? "UP" : "DOWN");
}

void default_message_callback(const TcpConnectionPtr &conn) {
    INFO("");
}


}
}