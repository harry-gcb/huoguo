#include "rtspclient.h"
#include "logger.h"

namespace huoguo {
namespace app {

RtspClient::RtspClient(net::EventLoop *loop)
    : m_loop(loop){
}

void RtspClient::pull(const std::string &url) {
    m_rtsp_puller = std::make_shared<rtsp::RtspClient>(m_loop, url);
    m_rtsp_puller->set_describe_response_callback(std::bind(&RtspClient::on_describe_response, this, std::placeholders::_1, std::placeholders::_2));
    m_rtsp_puller->start();
}

void RtspClient::push(const std::string &url) {
}

void RtspClient::on_describe_response(std::shared_ptr<rtsp::RtspSession> session, std::shared_ptr<rtsp::RtspDescribeResponse> response) {
    if (RTSP_SDP_TYPE == response->get_content_type()) {
        m_sdp.from_string(response->get_content_body());
        INFO("RtspClient::on_describe_response, sdp=\n%s", m_sdp.to_string().c_str());
    }
    
}

// void RtspClient::on_option_response(std::shared_ptr<rtsp::RtspSession> session, std::shared_ptr<rtsp::RtspOptionsResponse> response) {
//     auto message = session->handle_options_response(response);
//     if (!message) {
//         return;
//     }
//     auto connection = session->get_user_data();
//     connection->send(message->to_string());
// }

// void RtspClient::on_connect(std::shared_ptr<net::TcpConnection> conn) {
//     if (conn->is_connected()) {
//         m_rtsp_session = m_rtsp_client.create_session(m_rtsp_url);
//         m_rtsp_session->set_user_data(conn);
//         auto message = m_rtsp_session->do_options_request();
//         if (!message) {
//             ERROR("option request faild");
//         }
//         conn->send(message->to_string());
//     } else {
//         // m_rtsp_client.stop();
//     }
// }

// void RtspClient::on_message(std::shared_ptr<net::TcpConnection> conn, const uint8_t *data, size_t len) {
//     auto message = m_rtsp_session->on_message(data, len);
//     if (!message) {
//         return;
//     }
//     conn->send(message->to_string())
// }
// void RtspClient::on_session(std::shared_ptr<rtsp::RtspSession> session);

// void RtspClient::on_connect(std::shared_ptr<net::TcpConnection> conn) {
//     if (conn->is_connected()) {
//         INFO("[%s] rtsp_client connected", conn->get_trace_id().c_str());
//         m_session = std::make_shared<RtspSession>(conn, m_url);
//         m_session->set_options_response_callback(m_on_options_response);
//         m_session->set_describe_response_callback(m_on_describe_response);
//         m_session->set_setup_response_callback(m_on_setup_response);
//         m_session->set_play_response_callback(m_on_play_response);
//         m_session->set_teardown_response_callback(m_on_teardown_response);
//         if (m_on_start) {
//             m_on_start(m_session);
//         } else {
//             m_session->do_options_request();
//         }
//     } else {
//         INFO("[%s] rtsp_client disconnected", conn->get_trace_id().c_str());
//         if (m_on_stop) {
//             m_on_stop(m_session);
//         }
//         m_session.reset();
//     }
// }

// void RtspClient::start() {
//     m_client.start();
//     m_thread = std::thread(std::bind(&RtspClient::run, this));
// }

// void RtspClient::stop() {
//     m_stop = true;
//     m_loop.active_read_event();
// }

// void RtspClient::run() {
//     while (!m_stop) {
//         m_loop.run();
//     }
// }

}
}
