#ifndef HUOGUO_RTSP_RTSP_PLAY_H_
#define HUOGUO_RTSP_RTSP_PLAY_H_

#include "rtsp_request.h"
#include "rtsp_response.h"

namespace huoguo {
namespace rtsp {

class RtspPlayRequest: public RtspRequest{};
class RtspPlayResponse: public RtspResponse{};

} // namespace rtsp
} // namespace huoguo


#endif // HUOGUO_RTSP_RTSP_PLAY_H_