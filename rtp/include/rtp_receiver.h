#ifndef HUOGUO_RTP_RTP_RECEIVER_H_
#define HUOGUO_RTP_RTP_RECEIVER_H_

#include "event_loop.h"
#include "udp_client.h"

namespace huoguo {
namespace rtp {

class RtpReceiver {
public:
    RtpReceiver(net::EventLoop *loop, int port);
private:
    net::EventLoop *m_loop;
    net::UdpClient  m_client;
};

} // namespace rtp
} // namespace huoguo

#endif // HUOGUO_RTP_RTP_RECEIVER_H_