#ifndef HUOGUO_RTSP_RTSP_REQUEST_H_
#define HUOGUO_RTSP_RTSP_REQUEST_H_

#include "rtsp_message.h"
#include <string>

namespace huoguo {
namespace rtsp {

class RtspRequest: public RtspMessage {
public:
    RtspRequest(RTSP_MESSAGE_TYPE message_type, RTSP_METHOD method);
    void set_method(RTSP_METHOD method);
    void set_uri(const std::string &uri);
    void set_auth(const std::string &auth);
    std::string get_method() const;
    std::string get_uri() const;
    std::string get_request_line();
    virtual std::string to_string() override;
protected:
    RTSP_METHOD m_method;
    std::string m_uri;
};

}
}

#endif // HUOGUO_RTSP_RTSP_REQUESTS_H_