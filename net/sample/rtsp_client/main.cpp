#include "rtsp_client.h"
#include "logger.h"

int main(int argc, char *argv[]) {
    huoguo::net::EventLoop loop;
    huoguo::sample::RtspClient client(&loop, "rtsp://admin:Gcb@cc.1314@192.168.0.108:554");
    client.start();
    return loop.run();
}