#ifndef HUOGUO_RTSP_RTSP_TEARDOWN_H_
#define HUOGUO_RTSP_RTSP_TEARDOWN_H_

#include "rtsp_request.h"
#include "rtsp_response.h"

namespace huoguo {
namespace rtsp {

class RtspTeardownRequest: public RtspRequest{};
class RtspTeardownResponse: public RtspResponse{};

} // namespace rtsp
} // namespace huoguo

#endif // HUOGUO_RTSP_RTSP_TEARDOWN_H_