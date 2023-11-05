#ifndef HUOGUO_RTP_RTP_RECEIVER_H_
#define HUOGUO_RTP_RTP_RECEIVER_H_

// #include "net.h"
#include "net_udpserver.h"
#include "rtp_callback.h"
#include "rtp_session.h"

namespace huoguo {
namespace rtp {

class RtpReceiver {
public:
    RtpReceiver(net::EventLoop *loop, int port);

    void set_rtp_packet_callback(RtpPacketCallback callback);
    void start();
private:
    void on_message(const std::shared_ptr<net::UdpConnection> &connection, const net::InetAddr &addr, const uint8_t *data, size_t size);
private:
    net::EventLoop *m_loop;
    net::UdpServer  m_server;
    RtpPacketCallback m_callback;
    std::map<std::string, std::shared_ptr<RtpSession>> m_sessions;
};

} // namespace rtp
} // namespace huoguo

#endif // HUOGUO_RTP_RTP_RECEIVER_H_