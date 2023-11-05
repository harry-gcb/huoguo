#include "rtsp_client.h"
#include "utils_logger.h"

namespace huoguo {
namespace rtsp {

RtspClient::RtspClient(net::EventLoop *loop, const std::string &url)
    : m_loop(loop),
      m_url(url),
      m_client(loop, net::InetAddr(m_url.get_port(), m_url.get_ip()), "rtsp_client") {
    m_client.set_connect_callback(std::bind(&RtspClient::on_connect, this, std::placeholders::_1));
}

void RtspClient::start() {
    m_client.start();
}

void RtspClient::stop() {
    // m_client.stop();
}

void RtspClient::set_start_callback(Callback callback) {
    m_on_start = callback;
}
void RtspClient::set_stop_callback(Callback callback) {
    m_on_stop = callback;
}

void RtspClient::set_options_respone_callback(OptionsResponse callback) {
    m_on_options_response = callback;
}

void RtspClient::set_describe_response_callback(DescribeResponse callback) {
    m_on_describe_response = callback;
}

void RtspClient::set_setup_response_callback(SetupResponse callback) {
    m_on_setup_response = callback;
}

void RtspClient::set_play_response_callback(PlayResponse callback) {
    m_on_play_response = callback;
}

void RtspClient::set_teardown_response_callback(TeardownResponse callback) {
    m_on_teardown_response = callback;
}

void RtspClient::on_connect(std::shared_ptr<net::TcpConnection> conn) {
    if (conn->is_connected()) {
        InfoL("[%s] rtsp_client connected", conn->get_trace_id().c_str());
        m_session = std::make_shared<RtspSession>(conn, m_url);
        m_session->set_options_response_callback(m_on_options_response);
        m_session->set_describe_response_callback(m_on_describe_response);
        m_session->set_setup_response_callback(m_on_setup_response);
        m_session->set_play_response_callback(m_on_play_response);
        m_session->set_teardown_response_callback(m_on_teardown_response);
        if (m_on_start) {
            m_on_start(m_session);
        } else {
            m_session->do_options_request();
        }
    } else {
        InfoL("[%s] rtsp_client disconnected", conn->get_trace_id().c_str());
        if (m_on_stop) {
            m_on_stop(m_session);
        }
        m_session.reset();
    }
}

}
}