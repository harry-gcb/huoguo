#ifndef HUOGUO_RTSP_RTSP_RESPONSE_H_
#define HUOGUO_RTSP_RTSP_RESPONSE_H_

#include "rtsp_message.h"

namespace huoguo {
namespace rtsp {

class RtspResponse: public RtspMessage {
    class ResponseLine {
    public:
        int m_res_code;
        std::string m_res_desc;
        std::string m_version;
        ResponseLine() {}
        ResponseLine(int res_code, const std::string &res_desc, const std::string &version="RTSP/1.0")
            : m_res_code(res_code), m_res_desc(res_desc), m_version(version) {}
        std::string to_string() {
            return m_version + RTSP_SP + std::to_string(m_res_code) + RTSP_SP + m_res_desc + RTSP_CRLF;
        }
    };
public:
    RtspResponse(int res_code = 200, const std::string &res_desc = "OK", const std::string &version="RTSP/1.0");

    int get_res_code() const;
    std::string get_res_desc() const;

    int get_cseq() const;
    std::string get_www_authenticate() const;
    std::string get_content_type() const;
    std::string get_content_body() const;

    int parse_www_authenticate(std::string &auth_sln, std::string &auth_realm, std::string &auth_nonce);
    int parse_session(std::string &session_value);

    virtual std::string to_string() override;
    void clone_from(const RtspResponse &response);
private:
    ResponseLine m_response_line;
};

}
}


#endif