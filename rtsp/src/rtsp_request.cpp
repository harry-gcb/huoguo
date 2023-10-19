#include "rtsp_request.h"

namespace huoguo {
namespace rtsp {

RtspRequest::RtspRequest(const std::string &method, const std::string &uri, const std::string &version)
    : RtspMessage(true),
      m_request_line(method, uri, version) {
}

std::string RtspRequest::get_method() const {
    return m_request_line.m_method;
}

void RtspRequest::set_cseq(int cseq) {
    set_rtsp_header(RTSP_HEADER_FIELDS_CSEQ, std::to_string(cseq));
}

void RtspRequest::set_authorization(const std::string &authorization) {
    set_rtsp_header(RTSP_HEADER_FIELDS_AUTHORIZATION, authorization);
}

void RtspRequest::set_transport(const std::string &transport) {
    set_rtsp_header(RTSP_HEADER_FIELDS_TRANSPORT, transport);
}

void RtspRequest::set_session(const std::string &session) {
    set_rtsp_header(RTSP_HEADER_FIELDS_SESSION, session);
}

void RtspRequest::set_range(const std::string &range) {
    set_rtsp_header(RTSP_HEADER_FIELDS_RANGE, range);
}

std::string RtspRequest::to_string() {
    std::string request;
    request += m_request_line.to_string();
    request += RtspMessage::to_string();
    return request;
}

#if 0
RtspRequest::RtspRequest(RTSP_METHOD method)
    : m_method(method) {
    set_is_request(true);
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

#endif

}
}