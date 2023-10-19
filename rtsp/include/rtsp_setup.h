#ifndef HUOGUO_RTSP_RTSP_SETUP_H_
#define HUOGUO_RTSP_RTSP_SETUP_H_

#include "rtsp_request.h"
#include "rtsp_response.h"

namespace huoguo {
namespace rtsp {

class RtspSetupRequest: public RtspRequest {
public:
    RtspSetupRequest(const std::string &uri, const std::string &version = RTSP_VERSION) 
        : RtspRequest(SETUP, uri, version) {
    }
};

class RtspSetupResponse: public RtspResponse {
public:
    RtspSetupResponse(int res_code, const std::string &res_desc, const std::string &version=RTSP_VERSION)
        : RtspResponse(res_code, res_desc, version) {
    }
    RtspSetupResponse(const RtspResponse& response) {
        clone_from(response);
    }
};

} // namespace rtsp
} // namespace huoguo


#endif // HUOGUO_RTSP_RTSP_SETUP_H_