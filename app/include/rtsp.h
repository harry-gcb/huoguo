#ifndef HUOGUO_APP_RTSP_H_
#define HUOGUO_APP_RTSP_H_

#include <thread>
#include "event_loop.h"
#include "rtsp_client.h"

namespace huoguo {
namespace app {

class Rtsp {
public:
    Rtsp(const std::string &url);
    void start();
    void stop();
private:
    void run();
private:
    net::EventLoop m_loop;
    rtsp::RtspClient m_client;

    std::thread m_thread;
    bool m_stop;
    
};

} // namespace app
} // namespace huoguo

#endif // HUOGUO_APP_RTSP_H_