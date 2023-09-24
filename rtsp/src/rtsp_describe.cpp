#include "rtsp_describe.h"

namespace huoguo {
namespace rtsp {

//////////////////////////////////// RtspDescribeRequest ////////////////////////////////////

RtspDescribeRequest::RtspDescribeRequest(const std::string &uri, const std::string &version)
    : m_request(new RtspRequest(DESCRIBE, uri, version)) {
}

void RtspDescribeRequest::set_cseq(int cseq) {
    return m_request->set_rtsp_header(RTSP_HEADER_FIELDS_CSEQ, std::to_string(cseq));
}

void RtspDescribeRequest::set_authorization(const std::string &value) {
    m_request->set_rtsp_header(RTSP_HEADER_FIELDS_AUTHORIZATION, value);
}

std::shared_ptr<RtspRequest> RtspDescribeRequest::get_message() {
    return m_request;
}
//////////////////////////////////// RtspDescribeResponse ////////////////////////////////////

RtspDescribeResponse::RtspDescribeResponse(std::shared_ptr<RtspResponse> response)
    : m_response(response) {
}

std::string RtspDescribeResponse::get_content_type() const {
    return m_response->get_rtsp_header(RTSP_HEADER_FIELDS_CONTENT_TYPE);
}

std::string RtspDescribeResponse::get_content_body() const {
    return m_response->get_rtsp_body();
}

}
}