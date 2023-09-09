#ifndef HUOGUO_RTSP_RTSP_RESPONSE_H_
#define HUOGUO_RTSP_RTSP_RESPONSE_H_

#include "rtsp_message.h"

namespace huoguo {
namespace rtsp {

class RtspResponse: public RtspMessage {
public:
    RtspResponse(RTSP_MESSAGE_TYPE message_type, int status_code, const std::string &status_desc);
    virtual std::string to_string() override;
private:
    int m_status_code;
    std::string m_status_desc;
};

}
}


#endif