#ifndef HUOGUO_RTSP_RTSP_OPTIONS_H_
#define HUOGUO_RTSP_RTSP_OPTIONS_H_

#include <memory>
#include "rtsp_request.h"
#include "rtsp_response.h"

namespace huoguo {
namespace rtsp {

class RtspOptionsRequest: public RtspRequest {
public:
    RtspOptionsRequest(const std::string &uri, const std::string &version=RTSP_VERSION)
        : RtspRequest(OPTIONS, uri, version) {
    }
};

class RtspOptionsResponse: public RtspResponse {
public:
    RtspOptionsResponse(int res_code, const std::string &res_desc, const std::string &version=RTSP_VERSION)
        : RtspResponse(res_code, res_desc, version) {
    }
    RtspOptionsResponse(const RtspResponse& response) {
        clone_from(response);
    }
};

} // namespace rtsp
} // namespace huoguo

#endif // HUOGUO_RTSP_RTSP_OPTIONS_H_