#include "rtsp_options.h"

namespace huoguo {
namespace rtsp {

RtspOptionsRequest::RtspOptionsRequest(const std::string &request_uri)
    : RtspRequest(RTSP_MESSAGE_TYPE_OPTIONS_REQ, OPTIONS, request_uri) {

}

void RtspOptionsRequest::set_agent(const std::string &agent) {
    m_agent = agent; 
}

std::string RtspOptionsRequest::to_string() {
    std::string request_line = get_request_line();
    std::string request_header;
    request_header += RTSP_HEADER_FIELDS(RTSP_HEADER_FIELDS_CSEQ, std::to_string(m_cseq));
    if (!m_agent.empty()) {
        request_header += RTSP_HEADER_FIELDS(RTSP_HEADER_FIELDS_USER_AGENT, m_agent);
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

