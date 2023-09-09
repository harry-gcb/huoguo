#ifndef HUOGUO_RTSP_RTSP_MESSAGE_H_
#define HUOGUO_RTSP_RTSP_MESSAGE_H_

#include <string>
#include <map>
#include "rtsp_define.h"

namespace huoguo {
namespace rtsp {

class RtspMessage {
public:
    typedef enum RTSP_MESSAGE_TYPE {
        RTSP_MESSAGE_TYPE_OPTIONS_REQ,
        RTSP_MESSAGE_TYPE_OPTIONS_RSP,
    } RTSP_MESSAGE_TYPE;
public:
    RtspMessage(RTSP_MESSAGE_TYPE type);
    RTSP_MESSAGE_TYPE get_message_type() const;
    std::string get_version() const;
    void set_cseq(uint32_t cseq);
    uint32_t get_cseq() const;

    void set_field_with_value(const std::string &field, const std::string &value);

    virtual std::string to_string();
protected:
    RTSP_MESSAGE_TYPE m_message_type;
    std::string m_version;
    uint32_t m_cseq;

    std::map<std::string, std::string> m_fields;
};

} // rtsp
} // huoguo

#endif // HUOGUO_RTSP_RTSP_MESSAGE_H_