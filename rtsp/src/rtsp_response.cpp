#include "rtsp_response.h"

namespace huoguo {
namespace rtsp {

RtspResponse::RtspResponse(RTSP_MESSAGE_TYPE message_type, int status_code, const std::string &status_desc)
    : RtspMessage(message_type),
        m_status_code(status_code),
        m_status_desc(status_desc) {
}
std::string RtspResponse::to_string() {
    return "";
}

}
}