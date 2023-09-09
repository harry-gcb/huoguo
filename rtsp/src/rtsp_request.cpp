#include "rtsp_request.h"

namespace huoguo {
namespace rtsp {

RtspRequest::RtspRequest(RTSP_MESSAGE_TYPE message_type, RTSP_METHOD method, const std::string &url)
    : RtspMessage(message_type),
        m_method(method),
        m_url(url) {
}
void RtspRequest::set_method(RTSP_METHOD method) {
    m_method = method;
}
void RtspRequest::set_url(const std::string &url) {
    m_url = url;
}
std::string RtspRequest::get_request_line() {
    std::string request_line;
    request_line.append(rtsp_method[m_method]);
    request_line.append(RTSP_SP);
    request_line.append(m_url);
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