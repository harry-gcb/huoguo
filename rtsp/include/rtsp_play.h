#ifndef HUOGUO_RTSP_RTSP_PLAY_H_
#define HUOGUO_RTSP_RTSP_PLAY_H_

#include "rtsp_request.h"
#include "rtsp_response.h"

namespace huoguo {
namespace rtsp {

class RtspPlayRequest {
public:
    RtspPlayRequest(const std::string &uri, const std::string &version = RTSP_VERSION);

    void set_cseq(int cseq);
    void set_authorization(const std::string &value);

    std::shared_ptr<RtspRequest> get_message();
private:
    std::shared_ptr<RtspRequest> m_request;
};

class RtspPlayResponse: public RtspResponse{};

} // namespace rtsp
} // namespace huoguo


#endif // HUOGUO_RTSP_RTSP_PLAY_H_