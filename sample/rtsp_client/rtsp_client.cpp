#include "rtsp_client.h"
#include "callback.h"
#include "logger.h"

namespace huoguo {
namespace sample {

RtspClient::RtspClient(huoguo::net::EventLoop *loop, const std::string &url, bool tcp) 
    : m_loop(loop), 
      m_url(url),
      m_client(loop, huoguo::net::InetAddr(m_url.get_ip(), m_url.get_port()), "RtspClient") {
    m_client.set_connect_callback(std::bind(&RtspClient::on_connect, this, std::placeholders::_1));
    m_client.set_message_callback(std::bind(&RtspClient::on_message, this, std::placeholders::_1));
}

void RtspClient::start() {
    m_client.start();
}

void RtspClient::on_connect(const huoguo::net::TcpConnectionPtr &conn) {
    INFO("[RtspClient] %s:%d->%s:%d is %s", 
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

void RtspClient::on_message(const huoguo::net::TcpConnectionPtr &conn) {
    INFO("[RtspClient] receive message from %s:%d", conn->get_remote_ip().c_str(), conn->get_remote_port());
}


}
}