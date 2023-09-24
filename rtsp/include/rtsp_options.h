#ifndef HUOGUO_RTSP_RTSP_OPTIONS_H_
#define HUOGUO_RTSP_RTSP_OPTIONS_H_

#include <memory>
#include "rtsp_request.h"
#include "rtsp_response.h"

namespace huoguo {
namespace rtsp {

class RtspOptionsRequest {
public:
    RtspOptionsRequest(const std::string &uri, const std::string &version=RTSP_VERSION);
    RtspOptionsRequest(std::shared_ptr<RtspRequest> request = nullptr);

    std::string get_method() const;

    void set_cseq(int cseq);
    void set_authorization(const std::string &value);
    
    std::shared_ptr<RtspRequest> get_message();
private:
    std::shared_ptr<RtspRequest> m_request;
    std::string m_username;
    std::string m_password;
};

class RtspOptionsResponse {
public:
    RtspOptionsResponse(std::shared_ptr<RtspResponse> response);
    std::shared_ptr<RtspResponse> get_message() const;

    int get_cseq() const;
    std::string get_www_authenticate() const;
private:
    std::shared_ptr<RtspResponse> m_response;
};


} // namespace rtsp
} // namespace huoguo

#endif // HUOGUO_RTSP_RTSP_OPTIONS_H_