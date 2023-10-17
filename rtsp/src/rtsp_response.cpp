#include "rtsp_response.h"
#include "utils.h"
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

int RtspResponse::parse_www_authenticate(std::string &auth_sln, std::string &auth_realm, std::string &auth_nonce) {
    std::string www_authenticate = get_rtsp_header(RTSP_HEADER_FIELDS_WWW_AUTHENTICATE);
    if (utils::starts_with(www_authenticate, RTSP_AUTH_BASIC)) {
        auth_sln = RTSP_AUTH_BASIC;
    } else if (utils::starts_with(www_authenticate, RTSP_AUTH_DIGEST)) {
        auth_sln = RTSP_AUTH_DIGEST;
    } else {
        WarnL("auth not support, auth=%s", www_authenticate.c_str());
        return -1;
    }
    std::vector<std::string> authenticate_info = utils::split(www_authenticate.substr(auth_sln.length()), ",");
    for (size_t i = 0; i < authenticate_info.size(); ++i) {
        std::vector<std::string> kv = utils::split(authenticate_info[i], "=");
        if (kv.empty()) {
            continue;
        }
        std::string key = utils::trim(kv[0]);
        if (key.empty()) {
            continue;
        }
        if (RTSP_AUTH_REALM == utils::to_lower(key)) {
            auth_realm = kv.size() >= 2 ? utils::trim(utils::trim(kv[1]), "\"") : "";
        } else if (RTSP_AUTH_NONCE == utils::to_lower(key)) {
            auth_nonce = kv.size() >= 2 ? utils::trim(utils::trim(kv[1]), "\"") : "";
        }
    }
    return 0;
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