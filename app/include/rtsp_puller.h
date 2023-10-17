#ifndef HUOGUO_APP_RTSP_H_
#define HUOGUO_APP_RTSP_H_

#include <thread>
#include <any>
#include "net.h"
#include "rtsp_client.h"
#include "rtp_receiver.h"
#include "rtp_packet.h"
#include "sdp.h"

namespace huoguo {
namespace app {

class RtspPuller {
public:
    RtspPuller(net::EventLoop *loop);

    void pull(const std::string &url);
private:
    void on_describe_response(std::shared_ptr<rtsp::RtspSession> session, std::shared_ptr<rtsp::RtspDescribeResponse> response);

    void on_rtp_packet(const std::shared_ptr<rtp::RtpSession> &session, const std::shared_ptr<rtp::RtpPacket> &packet);
private:
    net::EventLoop *m_loop;
    std::shared_ptr<rtsp::RtspClient> m_rtsp_puller;
    std::shared_ptr<rtp::RtpReceiver> m_rtp_receiver;
    sdp::Sdp m_sdp;
};

} // namespace app
} // namespace huoguo

#endif // HUOGUO_APP_RTSP_H_