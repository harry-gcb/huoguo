#ifndef HUOGUO_RTSP_RTSP_SESSION_H_
#define HUOGUO_RTSP_RTSP_SESSION_H_

#include <map>
#include "tcp_connection.h"

namespace huoguo {
namespace rtsp {

class RtspSession {
public:
    RtspSession(std::shared_ptr<net::TcpConnection> conn);
private:
    void on_message(std::shared_ptr<net::TcpConnection> conn, const uint8_t *data, size_t len);
private:
    std::string m_trace_id;
    std::string m_buffer;

};

}
}

#endif // HUOGUO_RTSP_RTSP_SESSION_H_