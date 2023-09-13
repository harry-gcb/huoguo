#include "rtsp_session.h"
#include "rtsp_options.h"
#include "utils_string.h"
#include "utils_ssl.h"
#include "logger.h"

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
    m_connnection->set_message_callback(std::bind(&RtspSession::on_message, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

RtspSession::~RtspSession() {
    DEBUG("[%s] ~RtspSession", m_trace_id.c_str());
}

void RtspSession::do_options_request(std::shared_ptr<RtspOptionsRequest> request) {
    if (!request) {
        request = std::make_shared<RtspOptionsRequest>();
        request->set_uri(m_url.get_target_url());
    }
    m_state = RTSP_SESSION_STATE_OPTIONS;    
    request->set_cseq(++m_cseq);
    send_message(request);
}

void RtspSession::do_describe_request(std::shared_ptr<RtspDescribeRequest> request) {
    if (!request) {
        request = std::make_shared<RtspDescribeRequest>();
        request->set_uri(m_url.get_target_url());
    }
    if (m_need_authorize) {
        request->set_auth(m_auth_response);
    }
    m_state = RTSP_SESSION_STATE_DESCRIBE;    
    request->set_cseq(++m_cseq);
    send_message(request);
}

void RtspSession::do_setup_request(std::shared_ptr<RtspSetupRequest> request) {
    if (request) {
        request->set_cseq(++m_cseq);
        return send_message(request);
    }
}
void RtspSession::do_play_request(std::shared_ptr<RtspPlayRequest> request) {
    if (request) {
        request->set_cseq(++m_cseq);
        return send_message(request);
    }
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

void RtspSession::on_message(std::shared_ptr<net::TcpConnection> conn, const uint8_t *data, size_t len) {
    m_buffer.append(std::string((const char *)data));
    DEBUG("[%s] recv message from %s:%d with %d bytes\n%s", 
          m_trace_id.c_str(), conn->get_remote_ip().c_str(), conn->get_remote_port(), len, data);
    auto message = parse_message(m_buffer);
    if (!message) {
        WARN("[%s] message is not completed", m_trace_id.c_str());
        return;
    }
    handle_message(message);
}

void RtspSession::send_message(std::shared_ptr<RtspMessage> message) {
    if (!message) {
        return;
    }
    std::string buffer = message->to_string();
    m_connnection->send(buffer);
    DEBUG("[%s] send message to %s:%d with %d bytes\n%s", m_trace_id.c_str(), m_connnection->get_remote_ip().c_str(), m_connnection->get_remote_port(), buffer.length(), buffer.c_str());
}

void RtspSession::handle_message(std::shared_ptr<RtspMessage> message) {
    switch (message->get_message_type()) {
    case RtspMessage::RTSP_MESSAGE_TYPE_OPTIONS_REQ:
        INFO("[%s] not implement", m_trace_id.c_str());
        break;
    case RtspMessage::RTSP_MESSAGE_TYPE_OPTIONS_RSP:
        handle_options_response(std::dynamic_pointer_cast<RtspOptionsResponse>(message));
        break;
    default:
        break;
    }
}

void RtspSession::handle_options_response(std::shared_ptr<RtspOptionsResponse> response) {
    if (m_on_options_response) {
        return m_on_options_response(shared_from_this(), response);
    }
    if (!response || response->get_cseq() != m_cseq) {
        return;
    }
    if (response->get_status_code() == OK) {
        
        do_describe_request();
    } else if (response->get_status_code() == UNAUTHORIZED) {
        const std::string request_url = m_url.get_target_url();
        auto request = std::make_shared<RtspOptionsRequest>();
        m_auth_response = generate_auth(response->get_field(RTSP_HEADER_FIELDS_WWW_AUTHENTICATE), request->get_method(), request_url);
        request->set_uri(request_url);
        request->set_auth(m_auth_response);
        do_options_request(request);
    }
}

std::shared_ptr<RtspMessage> RtspSession::parse_message(std::string &buffer) {
    uint32_t readlen = 0;
    std::shared_ptr<RtspMessage> message = nullptr;
    auto rtsp_header_pos = buffer.find(RTSP_END);
    if (rtsp_header_pos == std::string::npos) {
        return message;
    }
    readlen += rtsp_header_pos+sizeof(RTSP_END);
    std::string rtsp_header = buffer.substr(0, rtsp_header_pos+sizeof(RTSP_END));
    if (utils::starts_with(rtsp_header, RTSP_VERSION))
    {
        message = parse_response(rtsp_header);
    } else {
        message = parse_request(rtsp_header);
    }
    if (message && message->get_content_length() > 0) {
        // TODO
        readlen += message->get_content_length();
    }
    if (m_buffer.length() <= readlen) {
        m_buffer.clear();
    } else {
        m_buffer = m_buffer.substr(readlen);
    }
    return message;
}

std::shared_ptr<RtspRequest> RtspSession::parse_request( std::string &buffer) {
    if (buffer.empty()) {
        return nullptr;
    }
    // auto line
    return nullptr;
}

std::shared_ptr<RtspResponse> RtspSession::parse_response( std::string &buffer) {
    if (buffer.empty()) {
        return nullptr;
    }
    auto rtsp_header = utils::split(buffer, RTSP_CRLF);
    if (rtsp_header.empty()) {
        WARN("[%s] error rtsp header, buffer=%s", m_trace_id.c_str(), buffer.c_str());
        return nullptr;
    }
    auto response = generate_response();
    if (!response) {
        return nullptr;
    }
    response->extract_response_line(rtsp_header[0]);
    response->extract_fields(rtsp_header);
    return response;
}

std::shared_ptr<RtspRequest> RtspSession::generate_request() {
    return nullptr;
}

std::shared_ptr<RtspResponse> RtspSession::generate_response() {
    switch (m_state) {
        case RTSP_SESSION_STATE_INIT:
            return nullptr;
        case RTSP_SESSION_STATE_OPTIONS:
            return std::make_shared<RtspOptionsResponse>();
        case RTSP_SESSION_STATE_DESCRIBE:
            return std::make_shared<RtspOptionsResponse>();
        default:
            return nullptr;
    }
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
        WARN("[%s] auth not support, auth=%s", m_trace_id.c_str(), www_authenticate.c_str());
        return m_auth_response;
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
        return m_auth_response;
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
    m_auth_response = authorization;
    return m_auth_response;
}

}
}