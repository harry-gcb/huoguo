#include "rtsp_teardown.h"

namespace huoguo {
namespace rtsp {

//////////////////////////////////// RtspTeardownRequest ////////////////////////////////////

RtspTeardownRequest::RtspTeardownRequest(const std::string &uri, const std::string &version)
    : m_request(new RtspRequest(SETUP, uri, version)) {
}

void RtspTeardownRequest::set_cseq(int cseq) {
    return m_request->set_rtsp_header(RTSP_HEADER_FIELDS_CSEQ, std::to_string(cseq));
}

void RtspTeardownRequest::set_authorization(const std::string &value) {
    m_request->set_rtsp_header(RTSP_HEADER_FIELDS_AUTHORIZATION, value);
}

std::shared_ptr<RtspRequest> RtspTeardownRequest::get_message() {
    return m_request;
}

}
}