#include "time_client.h"
#include "callback.h"
#include "logger.h"

namespace huoguo {
namespace sample {

TimeClient::TimeClient(huoguo::net::EventLoop *loop, const std::string &ip, int port) 
    : m_client(loop, huoguo::net::InetAddr(ip, port), "TimeClient") {
    m_client.set_connect_callback(std::bind(&TimeClient::on_connect, this, std::placeholders::_1));
    m_client.set_message_callback(std::bind(&TimeClient::on_message, this, std::placeholders::_1));
}

void TimeClient::start() {
    m_client.start();
}

void TimeClient::on_connect(const huoguo::net::TcpConnectionPtr &conn) {
    INFO("[TimeClient] %s:%d->%s:%d is %s", 
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

void TimeClient::on_message(const huoguo::net::TcpConnectionPtr &conn) {
    INFO("[TimeClient] receive message from %s:%d", conn->get_remote_ip().c_str(), conn->get_remote_port());
}


}
}