#include "rtsp_response.h"

namespace huoguo {
namespace rtsp {

RtspResponse::RtspResponse(RTSP_MESSAGE_TYPE message_type, int status_code, const std::string &status_desc)
    : RtspMessage(message_type),
        m_status_code(status_code),
        m_status_desc(status_desc) {
}

void RtspResponse::extract_response_line(const std::string &reponse_line) {
    int pos = 0;
    m_version = reponse_line.substr(0, strlen(RTSP_VERSION));
    pos += m_version.length();

    pos = reponse_line.find_first_not_of(RTSP_SP, pos);
    if (pos == std::string::npos || pos + RTSP_STATUS_CODE_LEN > reponse_line.length()) {
        return;
    }
    std::string status_code = reponse_line.substr(pos, RTSP_STATUS_CODE_LEN).c_str();
    pos += status_code.length();
    m_status_code = std::atoi(status_code.c_str());

    pos = reponse_line.find_first_not_of(RTSP_SP, pos);
    if (pos != std::string::npos) {
        m_status_desc = reponse_line.substr(pos);
    }
}

std::string RtspResponse::to_string() {
    return "";
}

}
}