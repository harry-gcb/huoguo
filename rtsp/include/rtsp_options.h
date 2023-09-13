#ifndef HUOGUO_RTSP_RTSP_OPTIONS_H_
#define HUOGUO_RTSP_RTSP_OPTIONS_H_

#include "rtsp_request.h"
#include "rtsp_response.h"

namespace huoguo {
namespace rtsp {

class RtspOptionsRequest: public RtspRequest {
public:
    RtspOptionsRequest();
    void set_agent(const std::string &agent);
    void set_username(const std::string &username);
    void set_password(const std::string &password);
    
    // std::string get_username() const;
    // std::string get_password() const;
    // std::string get_method() const;
    
    virtual std::string to_string() override;
private:
    std::string m_username;
    std::string m_password;
};

class RtspOptionsResponse: public RtspResponse {
public:
    RtspOptionsResponse(int status_code = OK, const std::string &status_desc = rtsp_status_map[OK]);
    virtual std::string to_string() override;
};

} // namespace rtsp
} // namespace huoguo

#endif // HUOGUO_RTSP_RTSP_OPTIONS_H_