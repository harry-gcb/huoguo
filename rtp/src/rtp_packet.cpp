#include "rtp_packet.h"
#include "utils_byte.h"

namespace huoguo {
namespace rtp {

#define RTP_DEFAULT_PACKET_SIZE 1500

RtpPacket::RtpPacket()
    : m_version(RTP_VERSION),
      m_padding(0),
      m_extension(0),
      m_number_of_csrc(0),
      m_marker(0),
      m_payload_type(0),
      m_sequence_number(0),
      m_timestamp(0),
      m_ssrc(0),
      m_payload_offset(0),
      m_payload_size(0),
      m_extension_offset(0),
      m_extension_size(0),
      m_extension_capacity(0),
      m_padding_size(0) {
}

uint8_t RtpPacket::get_version() {
    return m_version;
}

void RtpPacket::set_padding(uint8_t has_padding) {
    m_padding = has_padding;
}

uint8_t RtpPacket::get_padding() const {
    return m_padding;
}

void RtpPacket::set_extension(uint8_t has_extension) {
    m_extension = has_extension;
}

uint8_t RtpPacket::get_extension() const {
    return m_extension;
}

void RtpPacket::set_number_of_csrc(uint8_t number_of_csrc) {
    m_number_of_csrc = number_of_csrc;
}

uint8_t RtpPacket::get_number_of_csrc() const {
    return m_number_of_csrc;
}

void RtpPacket::set_marker(uint8_t marker) {
    m_marker = marker;
}
uint8_t RtpPacket::get_marker() const {
    return m_marker;
}

void RtpPacket::set_payload_type(uint8_t payload_type) {
    m_payload_type = payload_type;
}

uint8_t RtpPacket::get_payload_type() const {
    return m_payload_type;
}

void RtpPacket::set_sequence_number(uint16_t sequence_number) {
    m_sequence_number = sequence_number;
}

uint16_t RtpPacket::get_sequence_number() const {
    return m_sequence_number;
}

void RtpPacket::set_timestamp(uint32_t timestamp) {
    m_timestamp = timestamp;
}

uint32_t RtpPacket::get_timestamp() const {
    return m_timestamp;

}

void RtpPacket::set_ssrc(uint32_t ssrc) {
    m_ssrc = ssrc;
}

uint32_t RtpPacket::get_ssrc() const {
    return m_ssrc;
}

void RtpPacket::set_payload_offset(size_t payload_offset) {
    m_payload_offset = payload_offset;
}

size_t RtpPacket::get_payload_offset() const {
    return m_payload_offset;
}

void RtpPacket::set_payload_size(size_t payload_size) {
    m_payload_size = payload_size;
}

size_t RtpPacket::get_payload_size() const {
    return m_payload_size;
}

void RtpPacket::set_extension_offset(size_t extension_offset) {
    m_extension_offset = extension_offset;
}
size_t RtpPacket::get_extension_offset() const {
    return m_extension_offset;
}

void RtpPacket::set_extension_size(size_t extension_size) {
    m_extension_size = extension_size;
}
size_t RtpPacket::get_extension_size() const {
    return m_extension_size;
}

void RtpPacket::set_extension_capacity(size_t extension_capacity) {
    m_extension_capacity = extension_capacity;
}

size_t RtpPacket::get_extension_capacity() const {
    return m_extension_capacity;
}

RtpPacket::Extension &RtpPacket::find_or_create_extension(int id) {
    for (auto &extension: m_extension_entries) {
        if (extension.get_id() == id) {
            return extension;
        }
    }
    m_extension_entries.emplace_back(id);
    return m_extension_entries.back();
}

void RtpPacket::set_padding_size(uint8_t padding_size) {
    m_padding_size = padding_size;
}

uint8_t RtpPacket::get_padding_size() const {
    return m_padding_size;
}

void RtpPacket::set_buffer(const uint8_t *data, size_t size) {
    m_buffer.assign((const char *)data, size);
}

const std::string &RtpPacket::get_buffer() const {
    return m_buffer;
}

size_t RtpPacket::get_buffer_size() const {
    return m_buffer.length();
}

}
}