#include "rtsp_response.h"
#include "utils_string.h"
#include "utils_logger.h"
#include <cstring>

namespace huoguo {
namespace rtsp {

RtspResponse::RtspResponse(int res_code, const std::string &res_desc, const std::string &version)
    : RtspMessage(false),
      m_response_line(res_code, res_desc, version) {
}

std::string RtspResponse::to_string() {
    std::string response;
    response += m_response_line.to_string();
    response += RtspMessage::to_string();
    return response;
}

void RtspResponse::clone_from(const RtspResponse &response) {
    RtspMessage::clone_from(response);
    m_response_line = response.m_response_line;
}

int RtspResponse::get_cseq() const {
    return std::atoi(get_rtsp_header(RTSP_HEADER_FIELDS_CSEQ).c_str());
}

std::string RtspResponse::get_www_authenticate() const {
    return get_rtsp_header(RTSP_HEADER_FIELDS_WWW_AUTHENTICATE);
}

int RtspResponse::get_res_code() const {
    return m_response_line.m_res_code;
}
std::string RtspResponse::get_res_desc() const {
    return m_response_line.m_res_desc;
}

std::string RtspResponse::get_content_type() const {
    return get_rtsp_header(RTSP_HEADER_FIELDS_CONTENT_TYPE);
}

std::string RtspResponse::get_content_body() const {
    return get_rtsp_body();
}

int RtspResponse::parse_www_authenticate(std::string &auth_sln, std::string &auth_realm, std::string &auth_nonce) {
    std::string www_authenticate = get_rtsp_header(RTSP_HEADER_FIELDS_WWW_AUTHENTICATE);
    if (www_authenticate.empty()) {
        return -1;
    }
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

int RtspResponse::parse_session(std::string &session_value) {
    std::string session = get_rtsp_header(RTSP_HEADER_FIELDS_SESSION);
    if (session.empty()) {
        return -1;
    }
    std::vector<std::string> sesses = utils::split(session, ";");
    if (!sesses.empty()) {
        session_value = sesses[0];
    }
    return 0;
}



}
}