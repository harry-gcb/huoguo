#include "rtp_session.h"
#include "rtp_packet.h"
#include "utils_logger.h"

namespace huoguo {
namespace rtp {

RtpSession::RtpSession(std::shared_ptr<net::UdpConnection> connection)
    : m_connection(connection) {
    m_connection->set_message_callback(std::bind(&RtpSession::on_message, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
}

void RtpSession::on_message(const std::shared_ptr<net::UdpConnection> &connection, const net::InetAddr &addr, const uint8_t *data, size_t size) {
    if (m_callback) {
        auto rtp_packet = m_parser.parse(data, size);
        if (!rtp_packet) {
            WarnL("parse rtp data failed");
            return;
        }
        m_callback(shared_from_this(), rtp_packet);
    }
}

void RtpSession::set_rtp_packet_callback(RtpPacketCallback callback) {
    m_callback = callback;
}

}
}