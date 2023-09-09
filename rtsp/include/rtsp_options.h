#ifndef HUOGUO_RTSP_RTSP_OPTIONS_H_
#define HUOGUO_RTSP_RTSP_OPTIONS_H_

#include "rtsp_request.h"
#include "rtsp_response.h"

namespace huoguo {
namespace rtsp {

class RtspOptionsRequest: public RtspRequest {
public:
    RtspOptionsRequest(const std::string &request_uri);
    void set_agent(const std::string &agent);
    virtual std::string to_string() override;
private:
    std::string m_agent;
};

class RtspOptionsResponse: public RtspResponse {
public:
    RtspOptionsResponse(int status_code, const std::string &status_desc);
    virtual std::string to_string() override;
};

} // namespace rtsp
} // namespace huoguo

#endif // HUOGUO_RTSP_RTSP_OPTIONS_H_