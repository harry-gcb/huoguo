#include "rtsp_request.h"

namespace huoguo {
namespace rtsp {

RtspRequest::RtspRequest(RTSP_MESSAGE_TYPE message_type, RTSP_METHOD method)
    : RtspMessage(message_type),
      m_method(method) {
}
void RtspRequest::set_method(RTSP_METHOD method) {
    m_method = method;
}

void RtspRequest::set_uri(const std::string &uri) {
    m_uri = uri;
}

void RtspRequest::set_auth(const std::string &auth) {
    set_field(RTSP_HEADER_FIELDS_AUTHORIZATION, auth);
}

std::string RtspRequest::get_method() const {
    return rtsp_method_map[m_method];
}

std::string RtspRequest::get_uri() const {
    return m_uri;
}

std::string RtspRequest::get_request_line() {
    std::string request_line;
    request_line.append(rtsp_method_map[m_method]);
    request_line.append(RTSP_SP);
    request_line.append(m_uri);
    request_line.append(RTSP_SP);
    request_line.append(m_version);
    request_line.append(RTSP_CRLF);
    return request_line;
}

std::string RtspRequest::to_string() {
    return get_request_line();
}

}
}