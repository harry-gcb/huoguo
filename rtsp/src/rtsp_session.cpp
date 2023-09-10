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
      m_trace_id(conn->get_trace_id()),
      m_url(url),
      m_state(RTSP_SESSION_STATE_INIT),
      m_unauthorized(false),
      m_auth_sln(RTSP_AUTH_SLN_UNKNOWN),
      m_auth_count(0) {
    m_connnection->set_message_callback(std::bind(&RtspSession::on_message, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

RtspSession::~RtspSession() {
    DEBUG("[%s] ~RtspSession", m_trace_id.c_str());
}

void RtspSession::set_options_request_callback(OptionsRequest callback) {
    m_do_options_request = callback;
}

void RtspSession::do_options_request() {
    m_state = RTSP_SESSION_STATE_OPTIONS;
    const std::string request_url = m_url.get_target_url();
    auto request = std::make_shared<RtspOptionsRequest>(request_url);
    request->set_cseq(++m_cseq);
    if (m_do_options_request) {
        m_do_options_request(request);
    }
    if (m_unauthorized) {
        std::string auth_response;
        char authorization[RTSP_AUTH_SIZE] = { 0 };
        std::string username = m_url.get_username();
        std::string password = m_url.get_password();
        if ((username.empty() || password.empty()) && !m_auth_count) {
            username = request->get_username();
            password = request->get_password();
        }

        switch (m_auth_sln) {
            case RTSP_AUTH_SLN_BASIC:
                break;
            case RTSP_AUTH_SLN_DIGEST:
                auth_response = utils::md5(
                                utils::md5(username + ":" + m_auth_realm + ":" + password) + ":" + m_auth_nonce + ":" + 
                                utils::md5(request->get_method() + ":" + request_url));
                snprintf(authorization, sizeof(authorization), "%s username=\"%s\", realm=\"%s\", nonce=\"%s\", uri=\"%s\", response=\"%s\"",
                         RTSP_AUTH_DIGEST, username.c_str(), m_auth_realm.c_str(), m_auth_nonce.c_str(), request_url.c_str(), auth_response.c_str());
                break;
            default:
                break;
        }
        request->set_auth(authorization);
        m_unauthorized = false;
        m_auth_count++;
    }
    std::string req = request->to_string();
    DEBUG("[%s] send options request to %s:%d with %d bytes: \n%s", 
           m_trace_id.c_str(), m_connnection->get_remote_ip().c_str(), m_connnection->get_remote_port(), req.length(), req.c_str());
    m_connnection->send(req.c_str());
}

void RtspSession::do_describe_request() {

}


void RtspSession::on_message(std::shared_ptr<net::TcpConnection> conn, const uint8_t *data, size_t len) {
    m_buffer.append(std::string((const char *)data));
    DEBUG("[%s] recv message from %s:%d with %d bytes, \n%s", 
          m_trace_id.c_str(), conn->get_remote_ip().c_str(), conn->get_remote_port(), len, data);
    auto message = parse_message(m_buffer);
    if (!message) {
        WARN("[%s] message is not completed", m_trace_id.c_str());
        return;
    }
    handle_message(message);
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
    if (!response) {
        return;
    }
    if (response->get_cseq() != m_cseq) {
        return;
    }
    if (response->get_status_code() == OK) {
        do_describe_request();
    } else if (response->get_status_code() == UNAUTHORIZED) {
        std::string auth_way;
        std::vector<std::string> authenticate_info;
        std::string www_authenticate = response->get_field(RTSP_HEADER_FIELDS_WWW_AUTHENTICATE);
        if (utils::starts_with(www_authenticate, RTSP_AUTH_BASIC)) {
            auth_way = RTSP_AUTH_BASIC;
            m_auth_sln = RTSP_AUTH_SLN_BASIC;
        } else if (utils::starts_with(www_authenticate, RTSP_AUTH_DIGEST)) {
            auth_way = RTSP_AUTH_DIGEST;
            m_auth_sln = RTSP_AUTH_SLN_DIGEST;
        } else {
            WARN("[%s] auth not support, auth=%s", m_trace_id.c_str(), www_authenticate.c_str());
            return;
        }
        
        std::string key;
        std::string val;
        authenticate_info = utils::split(www_authenticate.substr(auth_way.length()), ",");
        for (size_t i = 0; i < authenticate_info.size(); ++i) {
            std::vector<std::string> kv = utils::split(authenticate_info[i], "=");
            if (kv.empty()) {
                continue;
            }
            key = utils::trim(kv[0]);
            if (key.empty()) {
                continue;
            }
            if (RTSP_AUTH_REALM == utils::to_lower(key)) {
                m_auth_realm = kv.size() >= 2 ? utils::trim(utils::trim(kv[1]), "\"") : "";
            } else if (RTSP_AUTH_NONCE == utils::to_lower(key)) {
                m_auth_nonce = kv.size() >= 2 ? utils::trim(utils::trim(kv[1]), "\"") : "";
            }
        }
        
        m_unauthorized = true;
        do_options_request();
    }
}

std::shared_ptr<RtspMessage> RtspSession::parse_message(std::string &buffer) {
    std::shared_ptr<RtspMessage> message = nullptr;
    auto rtsp_header_pos = buffer.find(RTSP_END);
    if (rtsp_header_pos == std::string::npos) {
        return message;
    }
    std::string rtsp_header = buffer.substr(0, rtsp_header_pos+sizeof(RTSP_END));
    if (utils::starts_with(rtsp_header, RTSP_VERSION))
    {
        message = parse_response(rtsp_header);
    } else {
        message = parse_request(rtsp_header);
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

std::shared_ptr<RtspResponse> RtspSession::generate_response(int status_code, const std::string &status_desc) {
    switch (m_state) {
        case RTSP_SESSION_STATE_INIT:
            return nullptr;
        case RTSP_SESSION_STATE_OPTIONS:
            return std::make_shared<RtspOptionsResponse>(status_code, status_desc);
        default:
            return nullptr;
    }
}

}
}