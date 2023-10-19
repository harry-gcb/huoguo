#ifndef HUOGUO_RTSP_RTSP_MESSAGE_H_
#define HUOGUO_RTSP_RTSP_MESSAGE_H_

#include <string>
#include <map>
#include <memory>
#include <vector>
#include <list>
#include "rtsp_define.h"

namespace huoguo {
namespace rtsp {

class RtspMessage {
    class RtspHeader {
        class Field {
        public:
            std::string m_field;
            std::string m_value;
            Field(const std::string &field, const std::string &value)
                : m_field(field), m_value(value) {}
        };
    public:
        void add_field(const std::string &field, const std::string &value) {
            m_header.push_back({field, value});
        }
        std::string get_field(const std::string &field) const {
            for (auto &item: m_header) {
                if (field == item.m_field) {
                    return item.m_value;
                }
            }
            return "";
        }
        std::string to_string() {
            std::string header;
            for (auto &item: m_header) {
                header += RTSP_HEADER_FIELDS(item.m_field, item.m_value);
            }
            return header;
        }
    private:
        std::list<Field> m_header;
    };
public:
    RtspMessage(bool is_request = true);
    bool is_request_message() const;

    void set_rtsp_header(const std::string &field, const std::string &value);
    void set_rtsp_body(const std::string &body);

    std::string get_rtsp_header(const std::string &field) const;
    std::string get_rtsp_body() const;

    virtual std::string to_string();
    void clone_from(const RtspMessage &message);
private:
    bool m_is_request;

    RtspHeader m_rtsp_header;
    std::string m_rtsp_body;
};

#if 0
class RtspMessage {
public:
    typedef enum RTSP_MESSAGE_TYPE {
        RTSP_MESSAGE_TYPE_OPTIONS_REQ,
        RTSP_MESSAGE_TYPE_OPTIONS_RSP,
        RTSP_MESSAGE_TYPE_DESCRIBE_REQ,
        RTSP_MESSAGE_TYPE_DESCRIBE_RSP,
    } RTSP_MESSAGE_TYPE;
public:
    RtspMessage();

    void set_message_type(RTSP_MESSAGE_TYPE type);
    RTSP_MESSAGE_TYPE get_message_type() const;

    void set_is_request(bool is_request);
    bool is_request_message() const;

    std::string get_version() const;
    void set_cseq(uint32_t cseq);
    uint32_t get_cseq() const;
    uint32_t get_content_length() const;

    void set_content(const std::string &content);
    std::string get_content() const;

    void extract_fields(const std::vector<std::string> &fields);
    void set_field(const std::string &field, const std::string &value);
    std::string get_field(const std::string &field) const;

    virtual void clone(const RtspMessage &message);
    virtual std::string to_string();
protected:
    bool m_is_request_message;
    RTSP_MESSAGE_TYPE m_message_type;
    std::string m_version;
    std::map<std::string, std::string> m_fields;
    std::string m_content;
};
#endif

} // rtsp
} // huoguo

#endif // HUOGUO_RTSP_RTSP_MESSAGE_H_