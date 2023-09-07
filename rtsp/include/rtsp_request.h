#ifndef HUOGUO_RTSP_RTSP_REQUEST_H_
#define HUOGUO_RTSP_RTSP_REQUEST_H_

#include "rtsp_define.h"
#include <string>

namespace huoguo {
namespace rtsp {

class RtspRequest {
public:
    RtspRequest(RTSP_METHOD method, const std::string &url, const std::string &version = RTSP_VERSION)
        : m_method(method),
          m_url(url),
          m_version(RTSP_VERSION) {
    }
    void set_method(RTSP_METHOD method) {
        m_method = method;
    }
    void set_url(const std::string &url) {
        m_url = url;
    }
    void set_version(const std::string &version) {
        m_version = version;
    }
    std::string get_request_line() {
        std::string request_line;
        request_line.append(rtsp_method[m_method]);
        request_line.append(RTSP_SP);
        request_line.append(m_url);
        request_line.append(RTSP_SP);
        request_line.append(m_version);
        request_line.append(RTSP_CRLF);
        return request_line;
    }
protected:
    RTSP_METHOD m_method;
    std::string m_url;
    std::string m_version;
};

}
}

#endif // HUOGUO_RTSP_RTSP_REQUESTS_H_