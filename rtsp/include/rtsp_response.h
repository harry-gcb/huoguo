#ifndef HUOGUO_RTSP_RTSP_RESPONSE_H_
#define HUOGUO_RTSP_RTSP_RESPONSE_H_

#include "rtsp_message.h"

namespace huoguo {
namespace rtsp {

class RtspResponse: public RtspMessage {
public:
    RtspResponse(RTSP_MESSAGE_TYPE message_type, int status_code = 200, const std::string &status_desc = rtsp_status_map[200]);
    void extract_response_line(const std::string &reponse_line);
    virtual std::string to_string() override;
private:
    int m_status_code;
    std::string m_status_desc;
};

}
}


#endif