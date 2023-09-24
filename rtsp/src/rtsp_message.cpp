#include "rtsp_message.h"
#include "utils_string.h"

namespace huoguo {
namespace rtsp {

RtspMessage::RtspMessage(bool is_request)
    : m_is_request(is_request) {
}

bool RtspMessage::is_request_message() const {
    return m_is_request;
}

void RtspMessage::set_rtsp_header(const std::string &field, const std::string &value) {
    m_rtsp_header.add_field(field, value);
}

void RtspMessage::set_rtsp_body(const std::string &body) {
    m_rtsp_body = body;
}

std::string RtspMessage::get_rtsp_header(const std::string &field) const {
    return m_rtsp_header.get_field(field);
}

std::string RtspMessage::get_rtsp_body() const {
    return m_rtsp_body;
}

std::string RtspMessage::to_string() {
    std::string message;
    message += m_rtsp_header.to_string() + RTSP_CRLF;
    message += m_rtsp_body;
    return message;
}

#if 0

RtspMessage::RTSP_MESSAGE_TYPE RtspMessage::get_message_type() const {
    return m_message_type;
}

void RtspMessage::set_is_request(bool is_request) {
    m_is_request_message = is_request;
}
bool RtspMessage::is_request_message() const {
    return m_is_request_message;
}

std::string RtspMessage::get_version() const {
    return m_version;
}

void RtspMessage::set_cseq(uint32_t cseq) {
    set_field(RTSP_HEADER_FIELDS_CSEQ, std::to_string(cseq));
}

uint32_t RtspMessage::get_cseq() const {
    return std::atoi(get_field(RTSP_HEADER_FIELDS_CSEQ).c_str());
}

uint32_t RtspMessage::get_content_length() const {
    return std::atoi(get_field(RTSP_HEADER_FIELDS_CONTENT_LENGTH).c_str());
}

void RtspMessage::extract_fields(const std::vector<std::string> &fields) {
    int pos = 0;
    for (size_t i = 1; i < fields.size(); ++i) {
        pos = fields[i].find_first_of(RTSP_COLON);
        if (pos == std::string::npos || pos == 0 || pos == fields[i].length() - 1) {
            continue;
        }
        std::string field = utils::trim(fields[i].substr(0, pos));
        std::string value = utils::trim(fields[i].substr(pos + 1));
        set_field(field, value);
    }
}

void RtspMessage::set_field(const std::string &field, const std::string &value) {
    m_fields[field] = value;
}

std::string RtspMessage::get_field(const std::string &field) const {
    auto it = m_fields.find(field);
    return it == m_fields.end() ? "" : it->second;
}

void RtspMessage::set_content(const std::string &content) {
    m_content = content;
}

std::string RtspMessage::get_content() const {
    return m_content;
}

void RtspMessage::clone(const RtspMessage &message) {
    m_is_request_message = message.m_is_request_message;
    m_message_type = message.m_message_type;
    m_version = message.m_version;
    m_fields = message.m_fields;
    m_content = message.m_content;
}

std::string RtspMessage::to_string() {
    // 用于调试
    std::string message;
    for (auto &item: m_fields) {
        message.append(item.first);
        message.append(RTSP_COLON);
        message.append(RTSP_SP);
        message.append(item.second);
        message.append(RTSP_CRLF);
    }
    // message.append(RTSP_CRLF);
    return message;
}
#endif

}
}