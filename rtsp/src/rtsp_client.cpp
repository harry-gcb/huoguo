#include "rtsp_client.h"

namespace huoguo {
namespace rtsp {

RtspClient::RtspClient(net::EventLoop *loop, const std::string &url)
    : m_loop(loop),
      m_url(url),
      m_client(loop, net::InetAddr(m_url.get_ip(), m_url.get_port()), "rtsp_client") {
    m_client.set_connect_callback(std::bind(&RtspClient::on_connect, this, std::placeholders::_1));
}

void RtspClient::start() {
    m_client.start();
}

void RtspClient::on_connect(std::shared_ptr<net::TcpConnection> conn) {
    if (conn->is_connected()) {
        auto session = std::make_shared<RtspSession>(conn);
        // session->do_options();
        m_sessions.insert({conn->get_trace_id(), session});
    } else {
        auto session = m_sessions.find(conn->get_trace_id());
        if (session != m_sessions.end()) {
            // session->second->do_shutdown();
            m_sessions.erase(session);
        }
    }
}

}
}