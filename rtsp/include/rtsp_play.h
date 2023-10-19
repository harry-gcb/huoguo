#ifndef HUOGUO_RTSP_RTSP_PLAY_H_
#define HUOGUO_RTSP_RTSP_PLAY_H_

#include "rtsp_request.h"
#include "rtsp_response.h"

namespace huoguo {
namespace rtsp {

class RtspPlayRequest: public RtspRequest {
public:
    RtspPlayRequest(const std::string &uri, const std::string &version = RTSP_VERSION)
        : RtspRequest(PLAY, uri, version) {
    }
};

class RtspPlayResponse: public RtspResponse {
public:
    RtspPlayResponse(int res_code, const std::string &res_desc, const std::string &version=RTSP_VERSION)
        : RtspResponse(res_code, res_desc, version) {
    }
};

} // namespace rtsp
} // namespace huoguo


#endif // HUOGUO_RTSP_RTSP_PLAY_H_