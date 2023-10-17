#ifndef NET_SAMPLE_UDP_ECHO_SERVER_H_
#define NET_SAMPLE_UDP_ECHO_SERVER_H_

#include "net.h"

namespace huoguo {
namespace sample {

class EchoServer {
public:
    EchoServer(net::EventLoop *loop, const std::string &host, int port)
        : m_server(loop, net::InetAddr(port, host, true), "udp_echo_server") {
        m_server.set_message_callback(std::bind(&EchoServer::on_message, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));

    }
    void start() {
        m_server.start();
    }
private:
    void on_message(const std::shared_ptr<net::UdpConnection> &conn, const net::InetAddr &addr, const char *data, int len) {
        InfoL("receive %d bytes: [%s]", len, data);
        conn->sendto(addr, data, len);
    };
private:
    net::UdpServer m_server;
    std::string m_host;
    int m_port;
};

#if 0

    : m_server(loop, net::InetAddr(port, "0.0.0.0", true), "rtsp_client") {
    m_server.set_datagram_callback(std::bind(&RtpReceiver::on_datagram_in, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

TimeServer::TimeServer(huoguo::net::EventLoop *loop, int port)
    : m_server(loop, huoguo::net::InetAddr(port), "TimeServer") {
    m_server.set_connect_callback(std::bind(&TimeServer::on_connect, this, std::placeholders::_1));
    m_server.set_message_callback(std::bind(&TimeServer::on_message, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

void TimeServer::start() {
    m_server.start();
}

void TimeServer::on_connect(std::shared_ptr<net::TcpConnection> conn) {
    InfoL("[TimeServer] %s:%d->%s:%d is %s", 
                        conn->get_remote_ip().c_str(), 
                        conn->get_remote_port(), 
                        conn->get_local_ip().c_str(),
                        conn->get_local_port(),
                        conn->is_connected() ? "UP" : "DOWN");
    if (conn->is_connected()) {
        time_t now = time(nullptr);
        // conn->send(&now, sizeof(now));
        // conn->shutdown();
    }
}

void TimeServer::on_message(std::shared_ptr<net::TcpConnection> conn, const char *data, size_t len) {
    InfoL("[TimeServer] receive message from %s:%d", conn->get_remote_ip().c_str(), conn->get_remote_port());
}


#endif

}
}

#endif