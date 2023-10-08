#ifndef HUOGUO_RTSP_RTSP_SETUP_H_
#define HUOGUO_RTSP_RTSP_SETUP_H_

#include "rtsp_request.h"
#include "rtsp_response.h"

namespace huoguo {
namespace rtsp {

class RtspSetupRequest {
public:
    RtspSetupRequest(const std::string &uri, const std::string &version = RTSP_VERSION);

    void set_cseq(int cseq);
    void set_authorization(const std::string &authorization);
    void set_transport(const std::string &transport);

    std::shared_ptr<RtspRequest> get_message();
private:
    std::shared_ptr<RtspRequest> m_request;
};

class RtspSetupResponse {
public:
    RtspSetupResponse(std::shared_ptr<RtspResponse> response);
    std::shared_ptr<RtspResponse> get_message() const;

    int get_cseq() const;
    std::string get_www_authenticate() const;
private:
    std::shared_ptr<RtspResponse> m_response;
};

} // namespace rtsp
} // namespace huoguo


#endif // HUOGUO_RTSP_RTSP_SETUP_H_