#ifndef HUOGUO_RTSP_RTSP_SERVER_H_
#define HUOGUO_RTSP_RTSP_SERVER_H_

#include "event_loop.h"

namespace huoguo {
namespace rtsp {

class RtspServer {
public:
    RtspServer(net::EventLoop *loop, const std::string &url);

    void start();
    void stop();

    void do_options_response();
    void do_describe_response();
    void do_setup_response();
    void do_play_response();
    void do_teardown_response();

    void set_options_request_callback();
    void set_describe_request_callback();
    void set_setup_request_callback();
    void set_play_request_callback();
    void set_teardown_request_callback();
};

}
}

#endif // HUOGUO_RTSP_RTSP_SERVER_H_