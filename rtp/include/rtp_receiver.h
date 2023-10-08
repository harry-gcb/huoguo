#ifndef HUOGUO_RTP_RTP_RECEIVER_H_
#define HUOGUO_RTP_RTP_RECEIVER_H_

#include "event_loop.h"
#include "udp_server.h"
#include "rtp_callback.h"

namespace huoguo {
namespace rtp {

class RtpReceiver {
public:
    RtpReceiver(net::EventLoop *loop, int port);

    void set_rtp_packet_callback(RtpPacketCallback callback);
    void start();
private:
    void on_datagram_in(std::shared_ptr<net::UdpConnection> connection, const char *data, int len);
private:
    net::EventLoop *m_loop;
    net::UdpServer  m_server;
    RtpPacketCallback m_callback;
};

} // namespace rtp
} // namespace huoguo

#endif // HUOGUO_RTP_RTP_RECEIVER_H_