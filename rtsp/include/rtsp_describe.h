#ifndef HUOGUO_RTSP_RTSP_DESCRIBE_H_
#define HUOGUO_RTSP_RTSP_DESCRIBE_H_

#include "rtsp_request.h"
#include "rtsp_response.h"

namespace huoguo {
namespace rtsp {

class RtspDescribeRequest: public RtspRequest {
public:
    RtspDescribeRequest(const std::string &uri, const std::string &version=RTSP_VERSION)
        : RtspRequest(DESCRIBE, uri, version) {
    }
};

class RtspDescribeResponse: public RtspResponse {
public:
    RtspDescribeResponse(int res_code, const std::string &res_desc, const std::string &version=RTSP_VERSION)
        : RtspResponse(res_code, res_desc, version) {
    }
    RtspDescribeResponse(const RtspResponse& response) {
        clone_from(response);
    }
};

} // namespace rtsp
} // namespace huoguo

#endif // HUOGUO_RTSP_RTSP_DESCRIBE_H_