#ifndef HUOGUO_RTSP_RTSP_OPTIONS_H_
#define HUOGUO_RTSP_RTSP_OPTIONS_H_

#include "rtsp_request.h"

namespace huoguo {
namespace rtsp {

class RtspOptions: public RtspRequest {
public:
    RtspOptions(const std::string &request_uri, int cseq): RtspRequest(OPTIONS, request_uri), m_cseq(cseq) {}

    void set_agent(const std::string &agent) { m_agent = agent; }

    std::string to_string();
private:
    uint32_t m_cseq;
    std::string m_agent;
};

} // namespace rtsp
} // namespace huoguo

#endif // HUOGUO_RTSP_RTSP_OPTIONS_H_