#include "rtsp_session.h"
#include "rtsp_options.h"
#include "utils.h"

namespace huoguo {
namespace rtsp {

RtspSession::RtspSession(std::shared_ptr<net::TcpConnection> conn, const RtspURL &url)
    : m_cseq(0),
      m_connnection(conn),
      m_trace_id(m_connnection->get_trace_id()),
      m_url(url),
      m_state(RTSP_SESSION_STATE_INIT),
      m_need_authorize(false),
      m_auth_sln(RTSP_AUTH_SLN_UNKNOWN) {
    m_connnection->set_message_callback(std::bind(&RtspSession::recv_message, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

RtspSession::~RtspSession() {
    InfoL("[%s] ~RtspSession", m_trace_id.c_str());
}

void RtspSession::do_options_request(std::shared_ptr<RtspOptionsRequest> request) {
    if (!request) {
        request = std::make_shared<RtspOptionsRequest>(m_url.get_target_url());
    }
    m_state = RTSP_SESSION_STATE_OPTIONS;    
    request->set_cseq(++m_cseq);
    send_message(request->get_message());
}

void RtspSession::do_describe_request(std::shared_ptr<RtspDescribeRequest> request) {
    if (!request) {
        request = std::make_shared<RtspDescribeRequest>(m_url.get_target_url());
    }
    if (m_need_authorize) {
        request->set_authorization(m_authorization);
    }
    m_state = RTSP_SESSION_STATE_DESCRIBE;    
    request->set_cseq(++m_cseq);
    send_message(request->get_message());
}

void RtspSession::do_setup_request(std::shared_ptr<RtspSetupRequest> request) {
    if (!request) {
        request = std::make_shared<RtspSetupRequest>(m_url.get_target_url());
    }
    if (m_need_authorize) {
        request->set_authorization(m_authorization);
    }
    m_state = RTSP_SESSION_STATE_SETUP;    
    request->set_cseq(++m_cseq);
    send_message(request->get_message());
}

void RtspSession::do_play_request(std::shared_ptr<RtspPlayRequest> request) {
    if (request) {
        request->set_cseq(++m_cseq);
        return send_message(request->get_message());
    }
}
void RtspSession::do_teardown_request(std::shared_ptr<RtspTeardownRequest> request) {
    if (request) {
        request->set_cseq(++m_cseq);
        return send_message(request->get_message());
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
    InfoL("[%s] recv message from %s:%d with %d bytes\n%s",
          m_trace_id.c_str(), conn->get_remote_ip().c_str(), conn->get_remote_port(), len, std::string(data, len).c_str());

    auto message = m_parser.parse((const char *)data, static_cast<int>(len));
    if (!message) {
        WarnL("[%s] message is not completed", m_trace_id.c_str());
        return;
    }
    if (message->is_request_message()) {
        return;
    }
    auto response = std::dynamic_pointer_cast<RtspResponse>(message);
    switch (m_state) {
    case RTSP_SESSION_STATE_INIT:
        break;
    case RTSP_SESSION_STATE_OPTIONS:
        handle_options_response(std::make_shared<RtspOptionsResponse>(response));
        break;
    case RTSP_SESSION_STATE_DESCRIBE:
        handle_describe_response(std::make_shared<RtspDescribeResponse>(response));
        break;
    case RTSP_SESSION_STATE_SETUP:
        handle_setup_response(std::make_shared<RtspSetupResponse>(response));
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

std::string RtspSession::generate_auth(const std::string &www_authenticate, const std::string &method, const std::string &uri) {
    m_need_authorize = true;
    std::string auth_way;
    RTSP_AUTH_SLN auth_sln = RTSP_AUTH_SLN_UNKNOWN;
    if (utils::starts_with(www_authenticate, RTSP_AUTH_BASIC)) {
        auth_way = RTSP_AUTH_BASIC;
        auth_sln = RTSP_AUTH_SLN_BASIC;
    } else if (utils::starts_with(www_authenticate, RTSP_AUTH_DIGEST)) {
        auth_way = RTSP_AUTH_DIGEST;
        auth_sln = RTSP_AUTH_SLN_DIGEST;
    } else {
        WarnL("[%s] auth not support, auth=%s", m_trace_id.c_str(), www_authenticate.c_str());
        return m_authorization;
    }
    std::vector<std::string> authenticate_info = utils::split(www_authenticate.substr(auth_way.length()), ",");
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
            m_auth_realm = kv.size() >= 2 ? utils::trim(utils::trim(kv[1]), "\"") : "";
        } else if (RTSP_AUTH_NONCE == utils::to_lower(key)) {
            m_auth_nonce = kv.size() >= 2 ? utils::trim(utils::trim(kv[1]), "\"") : "";
        }
    }

    std::string auth_response;
    char authorization[RTSP_AUTH_SIZE] = { 0 };
    std::string username = m_url.get_username();
    std::string password = m_url.get_password();
    if (username.empty() || password.empty()) {
        return m_authorization;
    }
    switch (auth_sln) {
        case RTSP_AUTH_SLN_BASIC:
            break;
        case RTSP_AUTH_SLN_DIGEST:
            auth_response = utils::md5(
                            utils::md5(username + ":" + m_auth_realm + ":" + password) + ":" + m_auth_nonce + ":" + 
                            utils::md5(method + ":" + uri));
            snprintf(authorization, sizeof(authorization), "%s username=\"%s\", realm=\"%s\", nonce=\"%s\", uri=\"%s\", response=\"%s\"",
                    RTSP_AUTH_DIGEST, username.c_str(), m_auth_realm.c_str(), m_auth_nonce.c_str(), uri.c_str(), auth_response.c_str());
            break;
        default:
            break;
    }
    m_authorization = authorization;
    return m_authorization;
}

std::string RtspSession::get_url() const {
    return m_url.get_target_url();
}


}
}