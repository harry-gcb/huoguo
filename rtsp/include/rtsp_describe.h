#ifndef HUOGUO_RTSP_RTSP_DESCRIBE_H_
#define HUOGUO_RTSP_RTSP_DESCRIBE_H_

#include "rtsp_request.h"
#include "rtsp_response.h"

namespace huoguo {
namespace rtsp {

class RtspDescribeRequest {
public:
    RtspDescribeRequest(const std::string &uri, const std::string &version=RTSP_VERSION);

    void set_cseq(int cseq);
    void set_authorization(const std::string &value);

    std::shared_ptr<RtspRequest> get_message();
private:
    std::shared_ptr<RtspRequest> m_request;
};

class RtspDescribeResponse {
public:
    RtspDescribeResponse(std::shared_ptr<RtspResponse> response);

    std::string get_content_type() const;
    std::string get_content_body() const;
private:
    std::shared_ptr<RtspResponse> m_response;
};

} // namespace rtsp
} // namespace huoguo

#endif // HUOGUO_RTSP_RTSP_DESCRIBE_H_