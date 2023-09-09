#include "rtsp_session.h"
#include "rtsp_options.h"
#include "strutils.h"
#include "logger.h"

namespace huoguo {
namespace rtsp {

RtspSession::RtspSession(std::shared_ptr<net::TcpConnection> conn, const RtspURL &url)
    : m_cseq(0),
      m_connnection(conn),
      m_trace_id(conn->get_trace_id()),
      m_url(url),
      m_state(RTSP_SESSION_STATE_INIT) {
    m_connnection->set_message_callback(std::bind(&RtspSession::on_message, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

RtspSession::~RtspSession() {
    DEBUG("[%s] ~RtspSession");
}

void RtspSession::set_options_request_callback(OptionsRequest callback) {
    m_do_options_request = callback;
}

void RtspSession::do_options_request() {
    m_state = RTSP_SESSION_STATE_OPTIONS;
    const std::string request_url;
    auto options_request = std::make_shared<RtspOptionsRequest>(request_url);
    options_request->set_cseq(++m_cseq);
    if (m_do_options_request) {
        m_do_options_request(options_request);
    }
    std::string r = options_request->to_string();
    DEBUG("\n===\n%s===", options_request->to_string().c_str());
    m_connnection->send(options_request->to_string());
}


void RtspSession::on_message(std::shared_ptr<net::TcpConnection> conn, const uint8_t *data, size_t len) {
    m_buffer.append(std::string((const char *)data));
    auto message = handle_message(m_buffer);
    if (!message) {
        WARN("[%s] message is not completed", m_trace_id.c_str());
        return;
    }
    // switch (m_state) {

    // }
    // auto message = try_parse_buffer_to_buffer(m_buffer);
    // switch (m_state) {
    // case RTSP_SESSION_STATE_OPTIONS:
    //     handle_options_response();
    //     break;
    // default:
    //     break;
    // }
    DEBUG("[%s] recv %d bytes, \n%s", m_trace_id.c_str(), len, data);
}

std::shared_ptr<RtspMessage> RtspSession::handle_message(std::string &buffer) {
    std::shared_ptr<RtspMessage> message = nullptr;
    auto rtsp_header_pos = buffer.find(RTSP_END);
    if (rtsp_header_pos == std::string::npos) {
        return message;
    }
    std::string rtsp_header = buffer.substr(0, rtsp_header_pos+sizeof(RTSP_END));
    auto rtsp_header_fields = utils::split(rtsp_header, RTSP_CRLF);
    if (rtsp_header_fields.empty()) {
        WARN("[%s] error rtsp header, buffer=%s", m_trace_id.c_str(), buffer.c_str());
        return message;
    }
    if (utils::starts_with(rtsp_header_fields[0], RTSP_VERSION))
    {
        DEBUG("[%s] received response, %s", m_trace_id.c_str(), rtsp_header_fields[0].c_str());
        message = handle_response(rtsp_header_fields);
        
    } else if (utils::ends_with(rtsp_header_fields[0], RTSP_VERSION)) {
        DEBUG("[%s] received request, %s", m_trace_id.c_str(), rtsp_header_fields[0].c_str());
        message = handle_request(rtsp_header_fields);
    } else {
        WARN("[%s] another rtsp version, %s", m_trace_id.c_str(), rtsp_header_fields[0].c_str());
    }
    return message;
}

std::shared_ptr<RtspMessage> RtspSession::handle_request(std::vector<std::string> &buffer) {
    if (buffer.empty()) {
        return nullptr;
    } else if (buffer[0].empty()) {
        return nullptr;
    }
    // auto line
    return nullptr;
}

std::shared_ptr<RtspMessage> RtspSession::handle_response(std::vector<std::string> &buffer) {
    std::shared_ptr<RtspMessage> message = nullptr;
    if (buffer.empty()) {
        return message;
    } else if (buffer[0].empty()) {
        return message;
    }

    auto pos = 0;
    std::string version;
    std::string status_code;
    std::string status_desc;
    // response header
    {
        auto reponse_line = buffer[0];
        version = reponse_line.substr(0, strlen(RTSP_VERSION));
        pos += version.length();

        pos = reponse_line.find_first_not_of(RTSP_SP, pos);
        if (pos == std::string::npos || pos + RTSP_STATUS_CODE_LEN > reponse_line.length()) {
            return nullptr;
        }
        status_code = reponse_line.substr(pos, RTSP_STATUS_CODE_LEN);
        pos += status_code.length();

        pos = reponse_line.find_first_not_of(RTSP_SP, pos);
        if (pos != std::string::npos) {
            status_desc = reponse_line.substr(pos);
        }
        DEBUG("[%s] reponse header line, version=%s, status=%s, desc=%s", m_trace_id.c_str(), version.c_str(), status_code.c_str(), status_desc.c_str());
    }

    switch (m_state) {
        case RTSP_SESSION_STATE_INIT:
            WARN("[%s] rtsp session init and get a response", m_trace_id.c_str());
            return message;
        case RTSP_SESSION_STATE_OPTIONS:
            message = std::make_shared<RtspOptionsResponse>(std::atoi(status_code.c_str()), status_desc);
            break;
    }

    // reponse header fields
    {
        int pos = 0;
        for (size_t i = 1; i < buffer.size(); ++i) {
            pos = buffer[i].find_first_of(RTSP_COLON);
            if (pos == std::string::npos || pos == 0 || pos == buffer[i].length() - 1) {
                continue;
            }
            std::string field = utils::trim(buffer[i].substr(0, pos-1));
            std::string value = utils::trim(buffer[i].substr(pos + 1));
            message->set_field_with_value(field, value);

            if (utils::starts_with(field, RTSP_HEADER_FIELDS_CSEQ)) {
                message->set_cseq(std::atoi(value.c_str()));
            } else if (utils::starts_with(field, RTSP_HEADER_FIELDS_WWW_AUTHENTICATE)) {
                
            }
        }
    }
    return nullptr;
}

}
}