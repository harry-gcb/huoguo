#ifndef HUOGUO_RTSP_CLIENT_H_
#define HUOGUO_RTSP_CLIENT_H_

#include "event_loop.h"
#include "tcp_client.h"
#include "rtsp_url.h"
#include "rtsp_session.h"
#include <string>
#include <map>

namespace huoguo {
namespace rtsp {

class RtspClient {
public:
    RtspClient(net::EventLoop *loop, const std::string &url);

    void start();

    void do_options_request();

    void set_options_respone_callback();



private:
    void on_connect(std::shared_ptr<net::TcpConnection> conn);
private:
    net::EventLoop *m_loop;
    rtsp::RtspURL   m_url;
    net::TcpClient  m_client;
    std::map<std::string, std::shared_ptr<rtsp::RtspSession>> m_sessions;
};

}
}

#endif // HUOGUO_RTSP_CLIENT_H_