#ifndef HUOGUO_APP_RTSP_H_
#define HUOGUO_APP_RTSP_H_

#include <thread>
#include <any>
#include "event_loop.h"
#include "rtsp_client.h"
#include "rtsp_session.h"
#include "sdp.h"

namespace huoguo {
namespace app {

class RtspPuller {
public:
    RtspPuller(net::EventLoop *loop);

    void pull(const std::string &url);
private:
    void on_describe_response(std::shared_ptr<rtsp::RtspSession> session, std::shared_ptr<rtsp::RtspDescribeResponse> response);
private:
    net::EventLoop *m_loop;
    std::shared_ptr<rtsp::RtspClient> m_rtsp_puller;
    std::shared_ptr<rtsp::RtspClient> m_rtsp_pusher;
    sdp::Sdp m_sdp;
};

} // namespace app
} // namespace huoguo

#endif // HUOGUO_APP_RTSP_H_