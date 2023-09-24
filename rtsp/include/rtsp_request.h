#ifndef HUOGUO_RTSP_RTSP_REQUEST_H_
#define HUOGUO_RTSP_RTSP_REQUEST_H_

#include "rtsp_message.h"
#include <string>

namespace huoguo {
namespace rtsp {

class RtspRequest: public RtspMessage {
    class RequestLine {
    public:
        std::string m_method;
        std::string m_uri;
        std::string m_version;
        RequestLine() {}
        RequestLine(const std::string &method, const std::string &uri, const std::string &version="RTSP/1.0")
            : m_method(method), m_uri(uri), m_version(version) {}
        std::string to_string() {
            return m_method + RTSP_SP + m_uri + RTSP_SP + m_version + RTSP_CRLF;
        }
    };
public:
    RtspRequest(const std::string &method, const std::string &uri, const std::string &version="RTSP/1.0");

    std::string get_method() const;

    virtual std::string to_string() override;
protected:
    RequestLine m_request_line;

};

}
}

#endif // HUOGUO_RTSP_RTSP_REQUESTS_H_