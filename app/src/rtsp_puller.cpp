#include "rtsp_puller.h"
#include "utils.h"
#include "rtp_portpool.h"

namespace huoguo {
namespace app {

RtspPuller::RtspPuller(net::EventLoop *loop)
    : m_loop(loop){
}

void RtspPuller::pull(const std::string &url) {

    // m_rtsp_client = std::make_shared<rtsp::RtspClient>(url);
    // auto rtsp_url = m_rtsp_client->get_rtsp_url();

    // m_tcp_client = std::make_shared<net::TcpClient>(m_loop, InetAddr())

    m_rtsp_puller = std::make_shared<rtsp::RtspClient>(m_loop, url);
    m_rtsp_puller->set_describe_response_callback(std::bind(&RtspPuller::on_describe_response, this, std::placeholders::_1, std::placeholders::_2));
    m_rtsp_puller->start();
}

void RtspPuller::on_describe_response(std::shared_ptr<rtsp::RtspSession> session, std::shared_ptr<rtsp::RtspDescribeResponse> response) {
    if (RTSP_SDP_TYPE == response->get_content_type()) {
        m_sdp.from_string(response->get_content_body());
        InfoL("RtspClient::on_describe_response, sdp=\n%s", m_sdp.to_string().c_str());
    }

    int rtp_port = 0;
    int rtcp_port = 0;
    if (!utils::Singleton<rtp::RtpPortPool>::getInstance().require_free_port_pair(rtp_port, rtcp_port)) {
        return;
    }

    std::string path;
    auto stream = m_sdp.get_stream("video");
    auto attributes = stream->get_attributes_list();
    for (auto &attribute: attributes) {
        if (!utils::starts_with(attribute, "control:")) {
            continue;
        }
        path = attribute.substr(strlen("control:"));
    }
    std::string transport;
    transport.append(stream->get_protocol());
    transport.append(";unicast;client_port=");
    transport.append(std::to_string(rtp_port) + "-" + std::to_string(rtcp_port));
    auto message = std::make_shared<rtsp::RtspSetupRequest>(session->get_url() + "/" + path);
    message->set_transport(transport);
    session->do_setup_request(message);


    m_rtp_receiver = std::make_shared<rtp::RtpReceiver>(m_loop, rtp_port);
    m_rtp_receiver->set_rtp_packet_callback(std::bind(&RtspPuller::on_rtp_packet, this, std::placeholders::_1));
    m_rtp_receiver->start();
    // m_rtp_receiver->add_data_observer();
}

void RtspPuller::on_rtp_packet(std::shared_ptr<rtp::RtpPacket> packet) {

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
//         InfoL("[%s] rtsp_client connected", conn->get_trace_id().c_str());
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
//         InfoL("[%s] rtsp_client disconnected", conn->get_trace_id().c_str());
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
