#include "rtsp_puller.h"
#include "rtp_portpool.h"
#include "utils_config.h"
#include "utils_string.h"
#include "utils_singleton.h"
#include "utils_logger.h"
#include "utils_singleton.h"

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
    m_rtsp_puller->set_setup_response_callback(std::bind(&RtspPuller::on_setup_response, this, std::placeholders::_1, std::placeholders::_2));
    m_rtsp_puller->start();
}

void RtspPuller::on_describe_response(std::shared_ptr<rtsp::RtspSession> session, std::shared_ptr<rtsp::RtspDescribeResponse> response) {
    if (RTSP_SDP_TYPE == response->get_content_type()) {
        m_sdp.from_string(response->get_content_body());
        InfoL("RtspClient::on_describe_response, sdp=\n%s", m_sdp.to_string().c_str());
    }

    size_t stream_count = m_sdp.stream_count();
    session->set_stream_count(m_sdp.stream_count());

    auto port_pair = utils::Singleton<rtp::RtpPortPool>::getInstance().require();
    if (!port_pair) {
        return;
    }

    std::string path;
    auto stream = m_sdp.get_stream(session->get_stream_index());
    auto attributes = stream->get_attributes_list();
    for (auto &attribute: attributes) {
        if (!utils::starts_with(attribute, "control:")) {
            continue;
        }
        path = attribute.substr(strlen("control:"));
    }
    std::string uri = session->get_url() + "/" + path;
    std::string transport;
    transport.append(stream->get_protocol());
    transport.append(";unicast;client_port=");
    transport.append(std::to_string(port_pair->get_rtp_port()) + "-" + std::to_string(port_pair->get_rtcp_port()));
    auto message = session->get_request_message<rtsp::RtspSetupRequest>(uri);
    message->set_transport(transport);
    session->do_setup_request(message);

    auto rtp_receiver = std::make_shared<rtp::RtpReceiver>(m_loop, port_pair->get_rtp_port());
    rtp_receiver->set_rtp_packet_callback(std::bind(&RtspPuller::on_rtp_packet, this, std::placeholders::_1, std::placeholders::_2));
    rtp_receiver->start();

    m_port_pairs.insert({uri, port_pair});
    m_rtp_receivers.insert({uri, rtp_receiver});

    session->set_stream_index(session->get_stream_index() + 1);
}

void RtspPuller::on_setup_response(std::shared_ptr<rtsp::RtspSession> session, std::shared_ptr<rtsp::RtspSetupResponse> response) {
    if (session->get_stream_index() < session->get_stream_count()) {
        auto port_pair = utils::Singleton<rtp::RtpPortPool>::getInstance().require();
        if (!port_pair) {
            return;
        }

        std::string path;
        auto stream = m_sdp.get_stream(session->get_stream_index());
        auto attributes = stream->get_attributes_list();
        for (auto &attribute: attributes) {
            if (!utils::starts_with(attribute, "control:")) {
                continue;
            }
            path = attribute.substr(strlen("control:"));
        }
        std::string uri = session->get_url() + "/" + path;
        std::string transport;
        transport.append(stream->get_protocol());
        transport.append(";unicast;client_port=");
        transport.append(std::to_string(port_pair->get_rtp_port()) + "-" + std::to_string(port_pair->get_rtcp_port()));
        auto message = session->get_request_message<rtsp::RtspSetupRequest>(uri);
        message->set_transport(transport);
        session->do_setup_request(message);

        auto rtp_receiver = std::make_shared<rtp::RtpReceiver>(m_loop, port_pair->get_rtp_port());
        rtp_receiver->set_rtp_packet_callback(std::bind(&RtspPuller::on_rtp_packet, this, std::placeholders::_1, std::placeholders::_2));
        rtp_receiver->start();

        m_port_pairs.insert({uri, port_pair});
        m_rtp_receivers.insert({uri, rtp_receiver});

        session->set_stream_index(session->get_stream_index() + 1);
    } else {
        auto message = session->get_request_message<rtsp::RtspPlayRequest>(session->get_url());
        message->set_range("npt=0.000-");
        session->do_play_request(message);
    }
}

void RtspPuller::on_rtp_packet(const std::shared_ptr<rtp::RtpSession> &session, const std::shared_ptr<rtp::RtpPacket> &packet) {
    static int count = 0;
    InfoL("%-3d, V=%d, P=%d, X=%d, CC=%d, M=%d, PT=%d, SN=%d, TS=%d, SSRC=%d", count++,
                        packet->get_version(),
                        packet->get_padding(),
                        packet->get_extension(),
                        packet->get_number_of_csrc(),
                        packet->get_marker(),
                        packet->get_payload_type(),
                        packet->get_sequence_number(),
                        packet->get_timestamp(),
                        packet->get_ssrc());
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

// void RtspClient::on_message(std::shared_ptr<net::TcpConnection> conn, const uint8_t *data, size_t size) {
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
