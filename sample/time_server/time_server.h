#ifndef HUOGUO_SAMPLE_TIME_SERVER_H_
#define HUOGUO_SAMPLE_TIME_SERVER_H_

#include <memory>

#include "event_loop.h"
#include "tcp_server.h"
#include "tcp_connection.h"

namespace huoguo {
namespace sample {

class TimeServer {
public:
    TimeServer(huoguo::net::EventLoop *loop, int port);
    void start();
private:
    void on_connect(const std::shared_ptr<huoguo::net::TcpConnection> &conn);
    void on_message(const std::shared_ptr<huoguo::net::TcpConnection> &conn);
private:
    huoguo::net::TcpServer m_server;
};

} // namespace sample
} // namespace huoguo

#endif // HUOGUO_SAMPLE_TIME_SERVER_H_