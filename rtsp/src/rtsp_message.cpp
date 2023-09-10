#include "rtsp_message.h"
#include "strutils.h"

namespace huoguo {
namespace rtsp {

RtspMessage::RtspMessage(RTSP_MESSAGE_TYPE type)
    : m_message_type(type), m_version(RTSP_VERSION) {

}

RtspMessage::RTSP_MESSAGE_TYPE RtspMessage::get_message_type() const {
    return m_message_type;
}

std::string RtspMessage::get_version() const {
    return m_version;
}

void RtspMessage::set_cseq(uint32_t cseq) {
    m_cseq = cseq;
}

uint32_t RtspMessage::get_cseq() const {
    return m_cseq;
}

void RtspMessage::extract_fields(const std::vector<std::string> &fields) {
    int pos = 0;
    for (size_t i = 1; i < fields.size(); ++i) {
        pos = fields[i].find_first_of(RTSP_COLON);
        if (pos == std::string::npos || pos == 0 || pos == fields[i].length() - 1) {
            continue;
        }
        std::string field = utils::trim(fields[i].substr(0, pos-1));
        std::string value = utils::trim(fields[i].substr(pos + 1));
        set_field(field, value);
    }
}

void RtspMessage::set_field(const std::string &field, const std::string &value) {
    m_fields[field] = value;
}

std::string RtspMessage::get_field(const std::string &field) {
    return m_fields[field];
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

}
}