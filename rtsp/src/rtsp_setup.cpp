#include "rtsp_setup.h"

namespace huoguo {
namespace rtsp {

//////////////////////////////////// RtspSetupRequest ////////////////////////////////////

RtspSetupRequest::RtspSetupRequest(const std::string &uri, const std::string &version)
    : m_request(new RtspRequest(SETUP, uri, version)) {
}

void RtspSetupRequest::set_cseq(int cseq) {
    return m_request->set_rtsp_header(RTSP_HEADER_FIELDS_CSEQ, std::to_string(cseq));
}

void RtspSetupRequest::set_authorization(const std::string &value) {
    m_request->set_rtsp_header(RTSP_HEADER_FIELDS_AUTHORIZATION, value);
}

std::shared_ptr<RtspRequest> RtspSetupRequest::get_message() {
    return m_request;
}

//////////////////////////////////// RtspSetupResponse ////////////////////////////////////
RtspSetupResponse::RtspSetupResponse(std::shared_ptr<RtspResponse> response)
    : m_response(response) {
}

std::shared_ptr<RtspResponse> RtspSetupResponse::get_message() const {
    return m_response;
}

int RtspSetupResponse::get_cseq() const {
    return std::atoi(m_response->get_rtsp_header(RTSP_HEADER_FIELDS_CSEQ).c_str());
}

std::string RtspSetupResponse::get_www_authenticate() const {
    return m_response->get_rtsp_header(RTSP_HEADER_FIELDS_WWW_AUTHENTICATE);
}

}
}