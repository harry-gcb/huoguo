#ifndef HUOGUO_RTSP_RTSP_SESSION_H_
#define HUOGUO_RTSP_RTSP_SESSION_H_

#include <map>
#include "tcp_connection.h"
#include "rtsp_callback.h"
#include "rtsp_url.h"

namespace huoguo {
namespace rtsp {

class RtspSession {
    typedef enum RTSP_SESSION_STATE {
        RTSP_SESSION_STATE_INIT = 0,
        RTSP_SESSION_STATE_OPTIONS = 1,
        RTSP_SESSION_STATE_UNKNOWN,
    } RTSP_SESSION_STATE;
public:
    RtspSession(std::shared_ptr<net::TcpConnection> conn, const RtspURL &url);
    ~RtspSession();

    void do_options_request();

    void set_options_request_callback(RtspOptionRequest callback);
private:
    void on_message(std::shared_ptr<net::TcpConnection> conn, const uint8_t *data, size_t len);
private:
    uint32_t m_seq;
    std::shared_ptr<net::TcpConnection> m_connnection;
    std::string m_trace_id;
    RtspURL m_url;
    RTSP_SESSION_STATE m_state;

    std::string m_buffer;

    RtspOptionRequest m_do_options_request;

    


};

}
}

#endif // HUOGUO_RTSP_RTSP_SESSION_H_