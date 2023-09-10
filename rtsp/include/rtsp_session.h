#ifndef HUOGUO_RTSP_RTSP_SESSION_H_
#define HUOGUO_RTSP_RTSP_SESSION_H_

#include <map>
#include "tcp_connection.h"
#include "rtsp_callback.h"
#include "rtsp_url.h"
#include "rtsp_message.h"

namespace huoguo {
namespace rtsp {

class RtspSession {
    typedef enum RTSP_SESSION_STATE {
        RTSP_SESSION_STATE_INIT = 0,
        RTSP_SESSION_STATE_OPTIONS = 1,
        RTSP_SESSION_STATE_UNKNOWN,
    } RTSP_SESSION_STATE;
    typedef enum RTSP_AUTH_SLN {
        RTSP_AUTH_SLN_UNKNOWN = 0,
        RTSP_AUTH_SLN_BASIC = 1,
        RTSP_AUTH_SLN_DIGEST = 2,
    } RTSP_AUTH_SLN;
public:
    RtspSession(std::shared_ptr<net::TcpConnection> conn, const RtspURL &url);
    ~RtspSession();

    void do_options_request();
    void do_describe_request();

    void set_options_request_callback(OptionsRequest callback);
private:
    void on_message(std::shared_ptr<net::TcpConnection> conn, const uint8_t *data, size_t len);
    void handle_message(std::shared_ptr<RtspMessage> message);

    void handle_options_response(std::shared_ptr<RtspOptionsResponse> response);

    std::shared_ptr<RtspMessage> parse_message(std::string &buffer);
    std::shared_ptr<RtspRequest> parse_request(std::string &buffer);
    std::shared_ptr<RtspResponse> parse_response(std::string &buffer);
    
    std::shared_ptr<RtspRequest> generate_request();
    std::shared_ptr<RtspResponse> generate_response(int status_code = OK, const std::string &status_desc = rtsp_status_map[OK]);
private:
    uint32_t m_cseq;
    std::shared_ptr<net::TcpConnection> m_connnection;
    std::string m_trace_id;
    RtspURL m_url;
    RTSP_SESSION_STATE m_state;
    bool m_unauthorized;
    RTSP_AUTH_SLN m_auth_sln;
    std::string m_auth_realm;
    std::string m_auth_nonce;
    int m_auth_count;
    
    std::string m_buffer;
    OptionsRequest m_do_options_request;

    
};

}
}

#endif // HUOGUO_RTSP_RTSP_SESSION_H_