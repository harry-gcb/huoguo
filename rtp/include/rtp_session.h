#ifndef HUOGUO_NET_RTP_SESSION_H_
#define HUOGUO_NET_RTP_SESSION_H_

#include "net_udpconnection.h"
#include "rtp_callback.h"
#include "rtp_parser.h"


namespace huoguo {
namespace rtp {

class RtpSession : public std::enable_shared_from_this<RtpSession> {
public:
    RtpSession(std::shared_ptr<net::UdpConnection> connection);
    void set_rtp_packet_callback(RtpPacketCallback callback);
    void on_message(const std::shared_ptr<net::UdpConnection> &connection, const net::InetAddr &addr, const uint8_t *data, size_t size);
private:
    std::shared_ptr<net::UdpConnection> m_connection;
    RtpPacketCallback m_callback;
    RtpParser m_parser;
};

}
}

#endif // HUOGUO_NET_RTP_SESSION_H_