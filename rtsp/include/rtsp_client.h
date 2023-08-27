#ifndef HUOGUO_RTSP_CLIENT_H_
#define HUOGUO_RTSP_CLIENT_H_

#include "event_loop.h"
#include <string>

namespace huoguo {
namespace rtsp {

class RtspClient {
public:
    RtspClient(net::EventLoop *loop, const std::string &url);
private:
    net::EventLoop *m_loop;
};

}
}

#endif // HUOGUO_RTSP_CLIENT_H_