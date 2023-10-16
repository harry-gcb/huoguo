#include "rtsp_session.h"
#include "utils.h"

namespace huoguo {
namespace rtsp {

void RtspSession::handle_options_response(std::shared_ptr<RtspOptionsResponse> response) {
    auto message = response->get_message()->to_string();
    if (m_on_options_response) {
        return m_on_options_response(shared_from_this(), response);
    }
    if (!response || response->get_cseq() != m_cseq) {
        WarnL("[%s] some wrong, %d, %d", m_trace_id.c_str(), response->get_cseq(), m_cseq);
        return;
    }
    if (response->get_message()->get_res_code() == OK) {
        do_describe_request();
    } else if (response->get_message()->get_res_code() == UNAUTHORIZED) {
        const std::string request_url = m_url.get_target_url();
        auto request = std::make_shared<RtspOptionsRequest>(OPTIONS, request_url);
        m_authorization = generate_auth(response->get_message()->get_rtsp_header(RTSP_HEADER_FIELDS_WWW_AUTHENTICATE), request->get_method(), request_url);
        request->set_authorization(m_authorization);
        do_options_request(request);
    }
}

void RtspSession::handle_describe_response(std::shared_ptr<RtspDescribeResponse> response) {
    if (m_on_describe_response) {
        return m_on_describe_response(shared_from_this(), response);
    }
    do_setup_request();
}

void RtspSession::handle_setup_response(std::shared_ptr<RtspSetupResponse> response) {
    if (m_on_setup_response) {
        return m_on_setup_response(shared_from_this(), response);
    }
    do_play_request();
}



}
}