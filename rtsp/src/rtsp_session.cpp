#include "rtsp_session.h"
#include "rtsp_options.h"
#include "strutils.h"
#include "logger.h"

namespace huoguo {
namespace rtsp {

RtspSession::RtspSession(std::shared_ptr<net::TcpConnection> conn, const RtspURL &url)
    : m_cseq(0),
      m_connnection(conn),
      m_trace_id(conn->get_trace_id()),
      m_url(url),
      m_state(RTSP_SESSION_STATE_INIT) {
    m_connnection->set_message_callback(std::bind(&RtspSession::on_message, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

RtspSession::~RtspSession() {
    DEBUG("[%s] ~RtspSession");
}

void RtspSession::set_options_request_callback(OptionsRequest callback) {
    m_do_options_request = callback;
}

void RtspSession::do_options_request() {
    m_state = RTSP_SESSION_STATE_OPTIONS;
    const std::string request_url;
    auto options_request = std::make_shared<RtspOptionsRequest>(request_url);
    options_request->set_cseq(++m_cseq);
    if (m_do_options_request) {
        m_do_options_request(options_request);
    }
    std::string r = options_request->to_string();
    DEBUG("\n===\n%s===", options_request->to_string().c_str());
    m_connnection->send(options_request->to_string());
}


void RtspSession::on_message(std::shared_ptr<net::TcpConnection> conn, const uint8_t *data, size_t len) {
    m_buffer.append(std::string((const char *)data));
    auto message = parse_message(m_buffer);
    if (!message) {
        WARN("[%s] message is not completed", m_trace_id.c_str());
        return;
    }
    // switch (m_state) {

    // }
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

std::shared_ptr<RtspMessage> RtspSession::parse_message(std::string &buffer) {
    std::shared_ptr<RtspMessage> message = nullptr;
    auto rtsp_header_pos = buffer.find(RTSP_END);
    if (rtsp_header_pos == std::string::npos) {
        return message;
    }
    std::string rtsp_header = buffer.substr(0, rtsp_header_pos+sizeof(RTSP_END));
    if (utils::starts_with(rtsp_header, RTSP_VERSION))
    {
        message = parse_response(rtsp_header);
    } else {
        message = parse_request(rtsp_header);
    }
    return message;
}

std::shared_ptr<RtspRequest> RtspSession::parse_request( std::string &buffer) {
    if (buffer.empty()) {
        return nullptr;
    }
    // auto line
    return nullptr;
}

std::shared_ptr<RtspResponse> RtspSession::parse_response( std::string &buffer) {
    if (buffer.empty()) {
        return nullptr;
    }
    auto rtsp_header = utils::split(buffer, RTSP_CRLF);
    if (rtsp_header.empty()) {
        WARN("[%s] error rtsp header, buffer=%s", m_trace_id.c_str(), buffer.c_str());
        return nullptr;
    }
    auto response = generate_response();
    if (!response) {
        return nullptr;
    }
    response->extract_response_line(rtsp_header[0]);
    response->extract_fields(rtsp_header);
    return response;
}

std::shared_ptr<RtspRequest> RtspSession::generate_request() {
    return nullptr;
}

std::shared_ptr<RtspResponse> RtspSession::generate_response(int status_code, const std::string &status_desc) {
    switch (m_state) {
        case RTSP_SESSION_STATE_INIT:
            return nullptr;
        case RTSP_SESSION_STATE_OPTIONS:
            return std::make_shared<RtspOptionsResponse>(status_code, status_desc);
        default:
            return nullptr;
    }
}

}
}