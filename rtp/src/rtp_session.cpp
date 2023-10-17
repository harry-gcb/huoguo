#include "rtp_session.h"
#include "rtp_packet.h"

namespace huoguo {
namespace rtp {

RtpSession::RtpSession(std::shared_ptr<net::UdpConnection> connection)
    : m_connection(connection) {
    m_connection->set_message_callback(std::bind(&RtpSession::on_message, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
}

void RtpSession::on_message(const std::shared_ptr<net::UdpConnection> &connection, const net::InetAddr &addr, const char *data, int length) {
    if (m_callback) {
        m_callback(shared_from_this(), std::make_shared<RtpPacket>());
    }
}

void RtpSession::set_rtp_packet_callback(RtpPacketCallback callback) {
    m_callback = callback;
}

}
}