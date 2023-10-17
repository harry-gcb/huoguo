#ifndef HUOGUO_NET_RTP_SESSION_H_
#define HUOGUO_NET_RTP_SESSION_H_

#include "net.h"
#include "rtp_callback.h"

namespace huoguo {
namespace rtp {

class RtpSession : public std::enable_shared_from_this<RtpSession> {
public:
    RtpSession(std::shared_ptr<net::UdpConnection> connection);
    void set_rtp_packet_callback(RtpPacketCallback callback);
    void on_message(const std::shared_ptr<net::UdpConnection> &connection, const net::InetAddr &addr, const char *data, int length);
private:
    std::shared_ptr<net::UdpConnection> m_connection;
    RtpPacketCallback m_callback;
};

}
}

#endif // HUOGUO_NET_RTP_SESSION_H_