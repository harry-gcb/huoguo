#ifndef HUOGUO_RTSP_RTSP_DESCRIBE_H_
#define HUOGUO_RTSP_RTSP_DESCRIBE_H_

#include "rtsp_request.h"
#include "rtsp_response.h"

namespace huoguo {
namespace rtsp {

class RtspDescribeRequest: public RtspRequest {
public:
    RtspDescribeRequest();
    virtual std::string to_string() override;
};
class RtspDescribeResponse: public RtspResponse {};

} // namespace rtsp
} // namespace huoguo

#endif // HUOGUO_RTSP_RTSP_DESCRIBE_H_