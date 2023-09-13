#include "rtsp_options.h"

namespace huoguo {
namespace rtsp {

RtspOptionsRequest::RtspOptionsRequest()
    : RtspRequest(RTSP_MESSAGE_TYPE_OPTIONS_REQ, OPTIONS) {
}

void RtspOptionsRequest::set_agent(const std::string &agent) {
    set_field(RTSP_HEADER_FIELDS_USER_AGENT, agent);
}

void RtspOptionsRequest::set_username(const std::string &username) {
    m_username = username;
}
void RtspOptionsRequest::set_password(const std::string &password) {
    m_password = password;
}

// std::string RtspOptionsRequest::get_username() const {
//     return m_username;
// }
// std::string RtspOptionsRequest::get_password() const {
//     return m_password;
// }

// std::string RtspOptionsRequest::get_method() {
//     return rtsp_method_map[OPTIONS];
// }

std::string RtspOptionsRequest::to_string() {
    std::string request_header;
    std::string request_line = get_request_line();
    std::string user_agent = get_field(RTSP_HEADER_FIELDS_USER_AGENT);
    std::string authorization = get_field(RTSP_HEADER_FIELDS_AUTHORIZATION);
    request_header += RTSP_HEADER_FIELDS(RTSP_HEADER_FIELDS_CSEQ, std::to_string(get_cseq()));
    if (!user_agent.empty()) {
        request_header += RTSP_HEADER_FIELDS(RTSP_HEADER_FIELDS_USER_AGENT, user_agent);
    }
    if (!authorization.empty()) {
        request_header += RTSP_HEADER_FIELDS(RTSP_HEADER_FIELDS_AUTHORIZATION, authorization);
    }
    request_header += RTSP_CRLF;
    return request_line + request_header;
}

RtspOptionsResponse::RtspOptionsResponse(int status_code, const std::string &status_desc)
    : RtspResponse(RTSP_MESSAGE_TYPE_OPTIONS_RSP, status_code, status_desc) {

}

std::string RtspOptionsResponse::to_string() {
    return "";
}

}
}

