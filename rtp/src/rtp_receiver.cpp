#include "rtp_receiver.h"

namespace huoguo {
namespace rtp {

RtpReceiver::RtpReceiver(net::EventLoop *loop, int port)
    : m_server(loop, net::InetAddr(port, "0.0.0.0", true), "rtsp_client") {
    m_server.set_message_callback(std::bind(&RtpReceiver::on_message, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
}

void RtpReceiver::set_rtp_packet_callback(RtpPacketCallback callback) {
    m_callback = callback;
}

void RtpReceiver::on_message(const std::shared_ptr<net::UdpConnection> &connection, const net::InetAddr &addr, const char *data, int len) {
}

void RtpReceiver::start() {

}

}
}