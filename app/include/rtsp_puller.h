#ifndef HUOGUO_APP_RTSP_H_
#define HUOGUO_APP_RTSP_H_

#include <map>
#include <thread>
#include <any>

#include "rtsp_session.h"
#include "rtsp_client.h"
#include "rtp_session.h"
#include "rtp_receiver.h"
#include "rtp_portpair.h"
#include "sdp_content.h"

namespace huoguo {
namespace app {

class RtspPuller {
public:
    RtspPuller(net::EventLoop *loop);

    void pull(const std::string &url);
private:
    void on_describe_response(std::shared_ptr<rtsp::RtspSession> session, std::shared_ptr<rtsp::RtspDescribeResponse> response);
    void on_setup_response(std::shared_ptr<rtsp::RtspSession> session, std::shared_ptr<rtsp::RtspSetupResponse> response);

    void on_rtp_packet(const std::shared_ptr<rtp::RtpSession> &session, const std::shared_ptr<rtp::RtpPacket> &packet);
private:
    net::EventLoop *m_loop;
    std::shared_ptr<rtsp::RtspClient> m_rtsp_puller;
    std::map<std::string, std::shared_ptr<rtp::RtpPortPair>> m_port_pairs;
    // std::map<std::string, rtp::RtpPortPair> m_port_pairs;
    std::map<std::string, std::shared_ptr<rtp::RtpReceiver>> m_rtp_receivers;

    sdp::SdpContent m_sdp;
};

} // namespace app
} // namespace huoguo

#endif // HUOGUO_APP_RTSP_H_