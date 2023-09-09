#include "rtsp_message.h"

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

void RtspMessage::set_field_with_value(const std::string &field, const std::string &value) {
    m_fields[field] = value;
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