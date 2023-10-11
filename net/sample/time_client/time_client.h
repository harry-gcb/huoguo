#ifndef HUOGUO_SAMPLE_TIME_CLIENT_H_
#define HUOGUO_SAMPLE_TIME_CLIENT_H_

#include <memory>

#include "net.h"
// #include "event_loop.h"
// #include "tcp_client.h"
// #include "tcp_connection.h"

namespace huoguo {
namespace sample {

class TimeClient {
public:
    TimeClient(huoguo::net::EventLoop *loop, const std::string &ip, int port);
    void start();
private:
    void on_connect(std::shared_ptr<net::TcpConnection> conn);
    void on_message(std::shared_ptr<net::TcpConnection> conn, const char *data, size_t len);
private:
    huoguo::net::TcpClient m_client;
};

}
}

#endif // HUOGUO_SAMPLE_TIME_CLIENT_H_