#ifndef HUOGUO_RTSP_RTSP_TEARDOWN_H_
#define HUOGUO_RTSP_RTSP_TEARDOWN_H_

#include "rtsp_request.h"
#include "rtsp_response.h"

namespace huoguo {
namespace rtsp {

class RtspTeardownRequest: public RtspRequest {
public:
    RtspTeardownRequest(const std::string &uri, const std::string &version=RTSP_VERSION)
        : RtspRequest(TEARDOWN, uri, version) {
    }
};

class RtspTeardownResponse: public RtspResponse {
public:
    RtspTeardownResponse(int res_code, const std::string &res_desc, const std::string &version=RTSP_VERSION)
        : RtspResponse(res_code, res_desc, version) {
    }
};

} // namespace rtsp
} // namespace huoguo

#endif // HUOGUO_RTSP_RTSP_TEARDOWN_H_