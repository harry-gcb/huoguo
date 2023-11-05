#ifndef HUOGUO_RTSP_CLIENT_H_
#define HUOGUO_RTSP_CLIENT_H_

#include <memory>
#include "event_loop.h"
#include "tcp_client.h"
#include "tcp_connection.h"
#include "rtsp_url.h"

namespace huoguo {
namespace sample {

class RtspClient {
public:
    RtspClient(huoguo::net::EventLoop *loop, const std::string &url, bool tcp = false);

    void start();
private:
    void on_connect(std::shared_ptr<net::TcpConnection> conn);
    void on_message(std::shared_ptr<net::TcpConnection> conn, const uint8_t *data, size_t size);
private:
    huoguo::net::EventLoop *m_loop;
    huoguo::rtsp::RtspURL   m_url;
    huoguo::net::TcpClient  m_client;
    
};

}
}

#endif