#ifndef HUOGUO_RTSP_RTSP_CLIENT_H_
#define HUOGUO_RTSP_RTSP_CLIENT_H_

#include "event_loop.h"
#include "tcp_client.h"
#include "rtsp_url.h"
#include "rtsp_session.h"
#include <string>
#include <map>

namespace huoguo {
namespace rtsp {

class RtspClient {
    using Callback = std::function<void (std::shared_ptr<RtspSession>)>;
public:
    RtspClient(net::EventLoop *loop, const std::string &url);

    void start();
    void stop();

    void set_start_callback(Callback callback);
    void set_stop_callback(Callback callback);

    void set_options_respone_callback(OptionsResponse callback);
    void set_describe_response_callback(DescribeResponse callback);
    void set_setup_response_callback(SetupResponse callback);
    void set_play_response_callback(PlayResponse callback);
    void set_teardown_response_callback(TeardownResponse callback);

private:
    void on_connect(std::shared_ptr<net::TcpConnection> conn);
private:
    net::EventLoop *m_loop;
    rtsp::RtspURL   m_url;
    net::TcpClient  m_client;
    std::shared_ptr<RtspSession> m_session;
    std::shared_ptr<RtspMessage> m_message;

    Callback m_on_start;
    Callback m_on_stop;

    OptionsResponse m_on_options_response;
    DescribeResponse m_on_describe_response;
    SetupResponse m_on_setup_response;
    PlayResponse m_on_play_response;
    TeardownResponse m_on_teardown_response;
};

} // namespace rtsp
} // namespace huoguo

#endif // HUOGUO_RTSP_RTSP_CLIENT_H_