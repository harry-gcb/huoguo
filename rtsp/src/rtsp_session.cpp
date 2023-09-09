#include "rtsp_session.h"
#include "logger.h"

namespace huoguo {
namespace rtsp {

RtspSession::RtspSession(std::shared_ptr<net::TcpConnection> conn, const RtspURL &url)
    : m_seq(0),
      m_connnection(conn),
      m_trace_id(conn->get_trace_id()),
      m_url(url),
      m_state(RTSP_SESSION_STATE_INIT) {
    m_connnection->set_message_callback(std::bind(&RtspSession::on_message, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

RtspSession::~RtspSession() {
    DEBUG("[%s] ~RtspSession");
}

void RtspSession::set_options_request_callback(RtspOptionRequest callback) {
    m_do_options_request = callback;
}

void RtspSession::do_options_request() {
    m_state = RTSP_SESSION_STATE_OPTIONS;
    const std::string request_url;
    auto options_request = std::make_shared<RtspOptions>(request_url, ++m_seq);
    if (m_do_options_request) {
        m_do_options_request(options_request);
    }
    std::string r = options_request->to_string();
    DEBUG("\n===\n%s===", options_request->to_string().c_str());
    m_connnection->send(options_request->to_string());
}


void RtspSession::on_message(std::shared_ptr<net::TcpConnection> conn, const uint8_t *data, size_t len) {
    m_buffer.append(std::string((const char *)data));
    // auto message = try_parse_buffer_to_buffer(m_buffer);
    // switch (m_state) {
    // case RTSP_SESSION_STATE_OPTIONS:
    //     handle_options_response();
    //     break;
    // default:
    //     break;
    // }
    DEBUG("[%s] recv %d bytes, \n%s", m_trace_id.c_str(), len, data);
}

std::shared_ptr<RtspMessage> RtspSession::handle_message(std::string &buffer);

}
}