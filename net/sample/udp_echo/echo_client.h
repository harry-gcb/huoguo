#ifndef HUOGUO_NET_SAMPLE_UDP_ECHO_CLIENT_H_
#define HUOGUO_NET_SAMPLE_UDP_ECHO_CLIENT_H_

#include "net_eventloop.h"
#include "net_udpclient.h"
#include "utils_logger.h"

namespace huoguo {
namespace sample {

class EchoClient {
public:
    EchoClient(net::EventLoop *loop, const std::string &host, int port, const std::string &echo, int count)
        : m_addr(port, host, true), 
          m_client(loop, m_addr, "udp_echo_client"),
          m_echo(echo),
          m_count(count),
          m_num(0) {
        m_client.set_message_callback(std::bind(&EchoClient::on_message, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));

    }
    void start() {
        m_client.sendto(m_addr, m_echo);
        m_num++;
    }
private:
    void on_message(const std::shared_ptr<net::UdpConnection> &conn, const net::InetAddr &addr, const uint8_t *data, size_t size) {
        InfoL("receive %d bytes: [%s]", size, data);
        if (m_num >= m_count) {
            return;
        }
        conn->sendto(addr, data, size);
        m_num++;
    };
private:
    net::InetAddr m_addr;
    net::UdpClient m_client;
    std::string m_echo;
    int m_count;
    int m_num;
};

}
}

#endif // HUOGUO_NET_SAMPLE_UDP_ECHO_CLIENT_H_