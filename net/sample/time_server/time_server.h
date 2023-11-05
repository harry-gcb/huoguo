#ifndef HUOGUO_SAMPLE_TIME_SERVER_H_
#define HUOGUO_SAMPLE_TIME_SERVER_H_

#include <memory>

#include "net_eventloop.h"
#include "net_tcpconnection.h"
#include "net_tcpserver.h"

namespace huoguo {
namespace sample {

class TimeServer {
public:
    TimeServer(net::EventLoop *loop, int port);
    void start();
private:
    void on_connect(std::shared_ptr<net::TcpConnection> conn);
    void on_message(std::shared_ptr<net::TcpConnection> conn, const uint8_t *data, size_t size);
private:
    net::TcpServer m_server;
};

} // namespace sample
} // namespace huoguo

#endif // HUOGUO_SAMPLE_TIME_SERVER_H_