#include "rtsp_play.h"

namespace huoguo {
namespace rtsp {

//////////////////////////////////// RtspPlayRequest ////////////////////////////////////

RtspPlayRequest::RtspPlayRequest(const std::string &uri, const std::string &version)
    : m_request(new RtspRequest(SETUP, uri, version)) {
}

void RtspPlayRequest::set_cseq(int cseq) {
    return m_request->set_rtsp_header(RTSP_HEADER_FIELDS_CSEQ, std::to_string(cseq));
}

void RtspPlayRequest::set_authorization(const std::string &value) {
    m_request->set_rtsp_header(RTSP_HEADER_FIELDS_AUTHORIZATION, value);
}

std::shared_ptr<RtspRequest> RtspPlayRequest::get_message() {
    return m_request;
}

}
}