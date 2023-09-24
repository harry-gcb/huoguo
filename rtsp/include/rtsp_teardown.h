#ifndef HUOGUO_RTSP_RTSP_TEARDOWN_H_
#define HUOGUO_RTSP_RTSP_TEARDOWN_H_

#include "rtsp_request.h"
#include "rtsp_response.h"

namespace huoguo {
namespace rtsp {

class RtspTeardownRequest {
public:
    RtspTeardownRequest(const std::string &uri, const std::string &version = RTSP_VERSION);

    void set_cseq(int cseq);
    void set_authorization(const std::string &value);

    std::shared_ptr<RtspRequest> get_message();
private:
    std::shared_ptr<RtspRequest> m_request;
};

class RtspTeardownResponse: public RtspResponse{};

} // namespace rtsp
} // namespace huoguo

#endif // HUOGUO_RTSP_RTSP_TEARDOWN_H_