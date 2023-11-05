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
    m_client.set_message_callback(std::bind(&RtspClient::on_message, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

void RtspClient::start() {
    m_client.start();
}

void RtspClient::on_connect(std::shared_ptr<net::TcpConnection> conn) {
    INFO("[RtspClient] %s:%d->%s:%d is %s", 
                        conn->get_remote_ip().c_str(), 
                        conn->get_remote_port(), 
                        conn->get_local_ip().c_str(),
                        conn->get_local_port(),
                        conn->is_connected() ? "UP" : "DOWN");
}

void RtspClient::on_message(std::shared_ptr<net::TcpConnection> conn, const uint8_t *data, size_t size) {

}


}
}