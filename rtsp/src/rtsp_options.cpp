#include "rtsp_options.h"

namespace huoguo {
namespace rtsp {

RtspOptionsRequest::RtspOptionsRequest(const std::string &uri, const std::string &version)
    : m_request(new RtspRequest(OPTIONS, uri, version)){
}

RtspOptionsRequest::RtspOptionsRequest(std::shared_ptr<RtspRequest> request)
    : m_request(request) {
}

std::string RtspOptionsRequest::get_method() const {
    return m_request->get_method();
}

void RtspOptionsRequest::set_cseq(int cseq) {
    return m_request->set_rtsp_header(RTSP_HEADER_FIELDS_CSEQ, std::to_string(cseq));
}

void RtspOptionsRequest::set_authorization(const std::string &value) {
    m_request->set_rtsp_header(RTSP_HEADER_FIELDS_AUTHORIZATION, value);
}

std::shared_ptr<RtspRequest> RtspOptionsRequest::get_message() {
    return m_request;
}

//////////////////////////////////// RtspOptionsResponse ////////////////////////////////////

RtspOptionsResponse::RtspOptionsResponse(std::shared_ptr<RtspResponse> response)
    : m_response(response) {
}

std::shared_ptr<RtspResponse> RtspOptionsResponse::get_message() const {
    return m_response;
}

int RtspOptionsResponse::get_cseq() const {
    return std::atoi(m_response->get_rtsp_header(RTSP_HEADER_FIELDS_CSEQ).c_str());
}

std::string RtspOptionsResponse::get_www_authenticate() const {
    return m_response->get_rtsp_header(RTSP_HEADER_FIELDS_WWW_AUTHENTICATE);
}

// std::string RtspOptionsResponse::to_string() {
//     return m_response->to_string();
// }

}
}

