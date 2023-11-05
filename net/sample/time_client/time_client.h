#ifndef HUOGUO_SAMPLE_TIME_CLIENT_H_
#define HUOGUO_SAMPLE_TIME_CLIENT_H_

#include <memory>

#include "net_eventloop.h"
#include "net_tcpclient.h"
namespace huoguo {
namespace sample {

class TimeClient {
public:
    TimeClient(huoguo::net::EventLoop *loop, const std::string &ip, int port);
    void start();
private:
    void on_connect(std::shared_ptr<net::TcpConnection> conn);
    void on_message(std::shared_ptr<net::TcpConnection> conn, const uint8_t *data, size_t size);
private:
    huoguo::net::TcpClient m_client;
};

}
}

#endif // HUOGUO_SAMPLE_TIME_CLIENT_H_