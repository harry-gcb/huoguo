#ifndef HUOGUO_RTSP_RTSP_SETUP_H_
#define HUOGUO_RTSP_RTSP_SETUP_H_

#include "rtsp_request.h"
#include "rtsp_response.h"

namespace huoguo {
namespace rtsp {

class RtspSetupRequest: public RtspRequest{};
class RtspSetupResponse: public RtspResponse{};

} // namespace rtsp
} // namespace huoguo


#endif // HUOGUO_RTSP_RTSP_SETUP_H_