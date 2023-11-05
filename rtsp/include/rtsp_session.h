#ifndef HUOGUO_RTSP_RTSP_SESSION_H_
#define HUOGUO_RTSP_RTSP_SESSION_H_

#include <map>
#include "net_eventloop.h"
#include "net_tcpconnection.h"
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
        RTSP_SESSION_STATE_PLAY = 4,
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

    template <typename T>
    std::shared_ptr<T> get_request_message(const std::string &uri);

    void set_session_id(uint32_t session_id);
    size_t get_session_id() const;
    void set_stream_count(size_t stream_count);
    size_t get_stream_count() const;
    void set_stream_index(size_t stream_index);
    size_t get_stream_index() const;

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
    void recv_message(std::shared_ptr<net::TcpConnection> conn, const uint8_t *data, size_t size);
    void send_message(std::shared_ptr<RtspMessage> message);

    void handle_response_pre(std::shared_ptr<RtspResponse> response);
    void handle_options_response(std::shared_ptr<RtspOptionsResponse> response);
    void handle_describe_response(std::shared_ptr<RtspDescribeResponse> response);
    void handle_setup_response(std::shared_ptr<RtspSetupResponse> response);

    std::string generate_auth(const std::string &method, const std::string &uri);
private:
    uint32_t m_cseq;
    std::shared_ptr<net::TcpConnection> m_connnection;
    std::string m_trace_id;
    RtspURL m_url;
    RTSP_SESSION_STATE m_state;

    bool m_need_authorize;
    std::string m_auth_sln;
    std::string m_auth_realm;
    std::string m_auth_nonce;
    
    std::string m_buffer;

    OptionsResponse m_on_options_response;
    DescribeResponse m_on_describe_response;
    SetupResponse m_on_setup_response;
    PlayResponse m_on_play_response;
    TeardownResponse m_on_teardown_response;

    RtspParser m_parser;

    size_t m_stream_index;
    size_t m_stream_count;
    std::string m_session_value;
    static uint32_t m_session_id;
};

template <typename T>
std::shared_ptr<T> RtspSession::get_request_message(const std::string &uri) {
    auto request = std::make_shared<T>(uri);
    request->set_cseq(++m_cseq);
    if (m_need_authorize) {
        request->set_authorization(generate_auth(request->get_method(), get_url()));
    }
    if (!m_session_value.empty()) {
        request->set_session(m_session_value);
    }
    return request;
}


}
}

#endif // HUOGUO_RTSP_RTSP_SESSION_H_