#include "rtsp_session.h"
#include "rtsp_options.h"
#include "utils.h"

namespace huoguo {
namespace rtsp {

uint32_t RtspSession::m_session_id = 0;

RtspSession::RtspSession(std::shared_ptr<net::TcpConnection> conn, const RtspURL &url)
    : m_cseq(0),
      m_connnection(conn),
      m_trace_id(m_connnection->get_trace_id()),
      m_url(url),
      m_state(RTSP_SESSION_STATE_INIT),
      m_need_authorize(false),
      m_stream_index(0),
      m_stream_count(0) {
    m_session_id++;
    m_connnection->set_message_callback(std::bind(&RtspSession::recv_message, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

RtspSession::~RtspSession() {
    InfoL("[%s] ~RtspSession", m_trace_id.c_str());
}

size_t RtspSession::get_session_id() const {
    return m_session_id;
}

void RtspSession::set_session_id(uint32_t session_id) {
    m_session_id = session_id;
}

void RtspSession::set_stream_count(size_t stream_count) {
    m_stream_count = stream_count;
}

size_t RtspSession::get_stream_count() const {
    return m_stream_count;
}

void RtspSession::set_stream_index(size_t stream_index) {
    m_stream_index = stream_index;
}
size_t RtspSession::get_stream_index() const {
    return m_stream_index;
}

void RtspSession::do_options_request(std::shared_ptr<RtspOptionsRequest> request) {
    if (!request) {
        request = get_request_message<RtspOptionsRequest>(get_url());
    }
    m_state = RTSP_SESSION_STATE_OPTIONS;    
    send_message(request);
}

void RtspSession::do_describe_request(std::shared_ptr<RtspDescribeRequest> request) {
    if (!request) {
        request = get_request_message<RtspDescribeRequest>(get_url());
    }
    m_state = RTSP_SESSION_STATE_DESCRIBE;    
    send_message(request);
}

void RtspSession::do_setup_request(std::shared_ptr<RtspSetupRequest> request) {
    if (!request) {
        request = get_request_message<RtspSetupRequest>(get_url());
    }
    m_state = RTSP_SESSION_STATE_SETUP;    
    send_message(request);
}

void RtspSession::do_play_request(std::shared_ptr<RtspPlayRequest> request) {
    if (!request) {
        request = get_request_message<RtspPlayRequest>(get_url());
    }
    m_state = RTSP_SESSION_STATE_PLAY;    
    send_message(request);
}

void RtspSession::do_teardown_request(std::shared_ptr<RtspTeardownRequest> request) {
    if (request) {
        request->set_cseq(++m_cseq);
        return send_message(request);
    }
}

void RtspSession::set_options_response_callback(OptionsResponse callback) {
    m_on_options_response = callback;
}
void RtspSession::set_describe_response_callback(DescribeResponse callback) {
    m_on_describe_response = callback;
}
void RtspSession::set_setup_response_callback(SetupResponse callback) {
    m_on_setup_response = callback;
}
void RtspSession::set_play_response_callback(PlayResponse callback) {
    m_on_play_response = callback;
}
void RtspSession::set_teardown_response_callback(TeardownResponse callback) {
    m_on_teardown_response = callback;
}

void RtspSession::recv_message(std::shared_ptr<net::TcpConnection> conn, const char *data, size_t len) {
    InfoL("[%s] state=%d, recv message from %s:%d with %d bytes\n%s",
          m_trace_id.c_str(), m_state, conn->get_remote_ip().c_str(), conn->get_remote_port(), len, std::string(data, len).c_str());

    auto message = m_parser.parse((const char *)data, static_cast<int>(len));
    if (!message) {
        WarnL("[%s] message is not completed", m_trace_id.c_str());
        return;
    }
    if (message->is_request_message()) {
        return;
    }
    auto response = std::dynamic_pointer_cast<RtspResponse>(message);
    handle_response_pre(response);
    switch (m_state) {
    case RTSP_SESSION_STATE_INIT:
        break;
    case RTSP_SESSION_STATE_OPTIONS:
        handle_options_response(std::make_shared<RtspOptionsResponse>(*response.get()));
        break;
    case RTSP_SESSION_STATE_DESCRIBE:
        handle_describe_response(std::make_shared<RtspDescribeResponse>(*response.get()));
        break;
    case RTSP_SESSION_STATE_SETUP:
        handle_setup_response(std::make_shared<RtspSetupResponse>(*response.get()));
        break;
    default:
        InfoL("[%s] not implement, %d", m_trace_id.c_str(), m_state);
    }
}

void RtspSession::send_message(std::shared_ptr<RtspMessage> message) {
    if (!message) {
        return;
    }
    std::string buffer = message->to_string();
    m_connnection->send(buffer);
    InfoL("[%s] send message to %s:%d with %d bytes\n%s", m_trace_id.c_str(), m_connnection->get_remote_ip().c_str(), m_connnection->get_remote_port(), buffer.length(), buffer.c_str());
}

std::string RtspSession::generate_auth(const std::string &method, const std::string &uri) {
    std::string auth_response;
    char authorization[RTSP_AUTH_SIZE] = { 0 };
    std::string username = m_url.get_username();
    std::string password = m_url.get_password();
    if (username.empty() || password.empty()) {
        return authorization;
    }
    if (RTSP_AUTH_BASIC == m_auth_sln) {
    } else if (RTSP_AUTH_DIGEST == m_auth_sln) {
        auth_response = utils::md5(
                        utils::md5(username + ":" + m_auth_realm + ":" + password) + ":" + m_auth_nonce + ":" + 
                        utils::md5(method + ":" + uri));
        snprintf(authorization, sizeof(authorization), "%s username=\"%s\", realm=\"%s\", nonce=\"%s\", uri=\"%s\", response=\"%s\"",
                RTSP_AUTH_DIGEST, username.c_str(), m_auth_realm.c_str(), m_auth_nonce.c_str(), uri.c_str(), auth_response.c_str());
    }
    return authorization;
}

std::string RtspSession::get_url() const {
    return m_url.get_target_url();
}


}
}