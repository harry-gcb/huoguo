#ifndef HUOGUO_RTSP_URL_H_
#define HUOGUO_RTSP_URL_H_

#include <string>

namespace huoguo {
namespace rtsp {

class RtspURL {
public:
    RtspURL(const std::string &url);

    bool parse(const std::string &url);

    std::string get_ip() const;
    uint16_t get_port() const;
    std::string get_username() const;
    std::string get_password() const;
    std::string get_target_url() const;
private:
    std::string m_url;

    std::string m_protocol;
    std::string m_auth;
    std::string m_username;
    std::string m_password;
    std::string m_ip;
    uint16_t    m_port;
    std::string m_path;
    std::string m_params;
};

} // namespace rtsp
} // namespace huoguo

#endif // HUOGUO_RTSP_URL_H_