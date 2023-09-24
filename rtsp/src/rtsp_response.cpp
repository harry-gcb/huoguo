#include "rtsp_response.h"
#include <cstring>

namespace huoguo {
namespace rtsp {

RtspResponse::RtspResponse(int res_code, const std::string &res_desc, const std::string &version)
    : RtspMessage(false),
      m_response_line(res_code, res_desc, version) {
}

int RtspResponse::get_res_code() const {
    return m_response_line.m_res_code;
}
std::string RtspResponse::get_res_desc() const {
    return m_response_line.m_res_desc;
}

std::string RtspResponse::to_string() {
    std::string response;
    response += m_response_line.to_string();
    response += RtspMessage::to_string();
    return response;
}

#if 0
RtspResponse::RtspResponse(int status_code, const std::string &status_desc)
    : m_status_code(status_code),
      m_status_desc(status_desc) {
    set_is_request(false);
}

int RtspResponse::get_status_code() const {
    return m_status_code;
}

std::string RtspResponse::get_status_desc() const {
    return m_status_desc;
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

void RtspResponse::clone(const RtspResponse &response) {
    RtspMessage::clone((RtspMessage)response);
    m_status_code = response.m_status_code;
    m_status_desc = response.m_status_desc;
}

std::string RtspResponse::to_string() {
    return "";
}
#endif

}
}