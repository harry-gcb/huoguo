#include "rtsp_session.h"
#include "utils_logger.h"

namespace huoguo {
namespace rtsp {

void RtspSession::handle_response_pre(std::shared_ptr<RtspResponse> response) {
    if (!response) {
        return;
    }
    if (response->get_res_code() == UNAUTHORIZED) {
        m_need_authorize = true;
        response->parse_www_authenticate(m_auth_sln, m_auth_realm, m_auth_nonce);
    }
    if (m_session_value.empty()) {
        response->parse_session(m_session_value);
    }
}

void RtspSession::handle_options_response(std::shared_ptr<RtspOptionsResponse> response) {
    if (m_on_options_response) {
        return m_on_options_response(shared_from_this(), response);
    }
    if (!response || response->get_cseq() != m_cseq) {
        WarnL("[%s] some wrong, %d, %d", m_trace_id.c_str(), response->get_cseq(), m_cseq);
        return;
    }
    if (response->get_res_code() == OK) {
        do_describe_request();
    } else if (response->get_res_code() == UNAUTHORIZED) {
        do_options_request();
    }
}

void RtspSession::handle_describe_response(std::shared_ptr<RtspDescribeResponse> response) {
    if (m_on_describe_response) {
        return m_on_describe_response(shared_from_this(), response);
    }
    do_setup_request();
}

void RtspSession::handle_setup_response(std::shared_ptr<RtspSetupResponse> response) {
    response->parse_session(m_session_value);
    if (m_on_setup_response) {
        return m_on_setup_response(shared_from_this(), response);
    }
    do_play_request();
}



}
}