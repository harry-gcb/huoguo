#ifndef HUOGUO_RTSP_RTSP_SESSION_H_
#define HUOGUO_RTSP_RTSP_SESSION_H_

#include <map>
#include "tcp_connection.h"
#include "rtsp_callback.h"
#include "rtsp_url.h"
#include "rtsp_message.h"
#include "rtsp_parser.h"

namespace huoguo {
namespace rtsp {

class RtspSession: public std::enable_shared_from_this<RtspSession> {
public:
    typedef enum RTSP_SESSION_STATE {
        RTSP_SESSION_STATE_INIT = 0,
        RTSP_SESSION_STATE_OPTIONS = 1,
        RTSP_SESSION_STATE_DESCRIBE = 2,
        RTSP_SESSION_STATE_SETUP = 3,
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

    void do_options_request(std::shared_ptr<RtspOptionsRequest> request = nullptr);
    void do_describe_request(std::shared_ptr<RtspDescribeRequest> request = nullptr);
    void do_setup_request(std::shared_ptr<RtspSetupRequest> request = nullptr);
    void do_play_request(std::shared_ptr<RtspPlayRequest> request = nullptr);
    void do_teardown_request(std::shared_ptr<RtspTeardownRequest> request = nullptr);

    void set_options_response_callback(OptionsResponse callback);
    void set_describe_response_callback(DescribeResponse callback);
    void set_setup_response_callback(SetupResponse callback);
    void set_play_response_callback(PlayResponse callback);
    void set_teardown_response_callback(TeardownResponse callback);

    std::string get_url() const;
private:
    void recv_message(std::shared_ptr<net::TcpConnection> conn, const char *data, size_t len);
    void send_message(std::shared_ptr<RtspMessage> message);
    
    void handle_options_response(std::shared_ptr<RtspOptionsResponse> response);
    void handle_describe_response(std::shared_ptr<RtspDescribeResponse> response);
    void handle_setup_response(std::shared_ptr<RtspSetupResponse> response);

    std::string generate_auth(const std::string &www_authenticate, const std::string &method, const std::string &uri);
private:
    uint32_t m_cseq;
    std::shared_ptr<net::TcpConnection> m_connnection;
    std::string m_trace_id;
    RtspURL m_url;
    RTSP_SESSION_STATE m_state;

    bool m_need_authorize;
    RTSP_AUTH_SLN m_auth_sln;
    std::string m_auth_realm;
    std::string m_auth_nonce;
    std::string m_authorization;
    
    std::string m_buffer;

    OptionsResponse m_on_options_response;
    DescribeResponse m_on_describe_response;
    SetupResponse m_on_setup_response;
    PlayResponse m_on_play_response;
    TeardownResponse m_on_teardown_response;

    RtspParser m_parser;
};

}
}

#endif // HUOGUO_RTSP_RTSP_SESSION_H_