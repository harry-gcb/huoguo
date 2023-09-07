#include "rtsp_options.h"

namespace huoguo {
namespace rtsp {

std::string RtspOptions::to_string() {
    std::string request_line = get_request_line();
    std::string request_header;
    request_header += RTSP_REQUEST_HEADER_FIELDS(RTSP_GERERAL_HEADER_FIELDS_CSEQ, std::to_string(m_cseq));
    if (!m_agent.empty()) {
        request_header += RTSP_REQUEST_HEADER_FIELDS(RTSP_REQUEST_HEADER_FIELDS_USER_AGENT, m_agent);
    }
    request_header += RTSP_CRLF;
    return request_line + request_header;
}

}
}

