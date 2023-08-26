#ifndef HUOGUO_SAMPLE_TIME_CLIENT_H_
#define HUOGUO_SAMPLE_TIME_CLIENT_H_

#include <memory>

#include "event_loop.h"
#include "tcp_client.h"
#include "tcp_connection.h"

namespace huoguo {
namespace sample {

class TimeClient {
public:
    TimeClient(huoguo::net::EventLoop *loop, const std::string &ip, int port);
    void start();
private:
    void on_connect(const std::shared_ptr<huoguo::net::TcpConnection> &conn);
    void on_message(const std::shared_ptr<huoguo::net::TcpConnection> &conn);
private:
    huoguo::net::TcpClient m_client;
};

}
}

#endif // HUOGUO_SAMPLE_TIME_CLIENT_H_