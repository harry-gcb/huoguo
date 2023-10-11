#ifndef HUOGUO_SAMPLE_TIME_SERVER_H_
#define HUOGUO_SAMPLE_TIME_SERVER_H_

#include <memory>

#include "net.h"

namespace huoguo {
namespace sample {

class TimeServer {
public:
    TimeServer(net::EventLoop *loop, int port);
    void start();
private:
    void on_connect(std::shared_ptr<net::TcpConnection> conn);
    void on_message(std::shared_ptr<net::TcpConnection> conn, const char *data, size_t len);
private:
    net::TcpServer m_server;
};

} // namespace sample
} // namespace huoguo

#endif // HUOGUO_SAMPLE_TIME_SERVER_H_