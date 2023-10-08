#include "time_server.h"
#include "callback.h"
#include "logger.h"

namespace huoguo {
namespace sample {

TimeServer::TimeServer(huoguo::net::EventLoop *loop, int port)
    : m_server(loop, huoguo::net::InetAddr(port), "TimeServer") {
    m_server.set_connect_callback(std::bind(&TimeServer::on_connect, this, std::placeholders::_1));
    m_server.set_message_callback(std::bind(&TimeServer::on_message, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

void TimeServer::start() {
    m_server.start();
}

void TimeServer::on_connect(std::shared_ptr<net::TcpConnection> conn) {
    INFO("[TimeServer] %s:%d->%s:%d is %s", 
                        conn->get_remote_ip().c_str(), 
                        conn->get_remote_port(), 
                        conn->get_local_ip().c_str(),
                        conn->get_local_port(),
                        conn->is_connected() ? "UP" : "DOWN");
    if (conn->is_connected()) {
        time_t now = time(nullptr);
        // conn->send(&now, sizeof(now));
        // conn->shutdown();
    }
}

void TimeServer::on_message(std::shared_ptr<net::TcpConnection> conn, const char *data, size_t len) {
    INFO("[TimeServer] receive message from %s:%d", conn->get_remote_ip().c_str(), conn->get_remote_port());
}

} // end of namespace sample
} // end of namespace huoguo