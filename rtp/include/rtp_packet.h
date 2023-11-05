#ifndef HUOGUO_RTP_RTP_PACKET_H_
#define HUOGUO_RTP_RTP_PACKET_H_

#include <string>
#include <vector>
#include <cstdint>
#include "utils_noncopyable.h"

#define RTP_VERSION 2
#define RTP_FIXED_HEADER_SIZE 12
#define RTP_ONE_BYTE_EXT_PROFILE_ID 0xBEDE
#define RTP_TWO_BYTE_EXT_PROFILE_ID 0x1000
#define RTP_TWO_BYTE_EXT_PROFILE_ID_APP_BITS_FILTER 0xFFF0
#define RTP_ONE_BYTE_EXT_HEADER_LEN 1
#define RTP_TWO_BYTE_EXT_HEADER_LEN 2
#define RTP_DEFAULT_PACKET_SIZE 1500

namespace huoguo {
namespace rtp {

class RtpPacket : public utils::Noncopyable {
public:
    class Extension {
    public:
        explicit Extension(uint8_t id)
            : m_id(id), m_length(0), m_offset(0) {}
        
        void set_id(uint8_t id) { m_id = id; }
        uint8_t get_id() const { return m_id; }
        void set_length(uint8_t length) { m_length = length; }
        uint8_t get_length() const { return m_length; }
        void set_offset(uint8_t offset) { m_offset = offset; }
        uint16_t get_offset() const { return m_offset; }
    private:
        uint8_t m_id;
        uint8_t m_length;
        uint16_t m_offset;
    };
public:
    RtpPacket();

    uint8_t get_version();

    void set_padding(uint8_t padding);
    uint8_t get_padding() const;

    void set_extension(uint8_t extension);
    uint8_t get_extension() const;

    void set_number_of_csrc(uint8_t number_of_csrc);
    uint8_t get_number_of_csrc() const;

    void set_marker(uint8_t marker);
    uint8_t get_marker() const;

    void set_payload_type(uint8_t payload_type);
    uint8_t get_payload_type() const;

    void set_sequence_number(uint16_t sequence_number);
    uint16_t get_sequence_number() const;

    void set_timestamp(uint32_t timestamp);
    uint32_t get_timestamp() const;

    void set_ssrc(uint32_t ssrc);
    uint32_t get_ssrc() const;

    void set_payload_offset(size_t payload_offset);
    size_t get_payload_offset() const;

    void set_payload_size(size_t payload_size);
    size_t get_payload_size() const;

    void set_extension_offset(size_t extension_offset);
    size_t get_extension_offset() const;

    void set_extension_size(size_t extension_size);
    size_t get_extension_size() const;

    void set_extension_capacity(size_t extension_capacity);
    size_t get_extension_capacity() const;

    Extension &find_or_create_extension(int id);

    void set_padding_size(uint8_t padding_size);
    uint8_t get_padding_size() const;

    void set_buffer(const uint8_t *data, size_t size);
    const std::string &get_buffer() const;
    size_t get_buffer_size() const;
private:
    // 第1字节
    uint8_t m_version;
    uint8_t m_padding;
    uint8_t m_extension;
    uint8_t m_number_of_csrc;
    // 第2字节
    uint8_t m_marker;
    uint8_t m_payload_type;
    // 第3-4字节
    uint16_t m_sequence_number;
    // 第5-8字节
    uint32_t m_timestamp;
    // 第9-12字节
    uint32_t m_ssrc;

    size_t m_payload_offset;
    size_t m_payload_size;

    size_t m_extension_offset;
    size_t m_extension_size;
    size_t m_extension_capacity;

    std::vector<Extension> m_extension_entries;

    uint8_t m_padding_size;

    std::string m_buffer;
};

}
}

#endif // HUOGUO_RTP_RTP_PACKET_H_