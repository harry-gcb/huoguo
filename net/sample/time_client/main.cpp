#include "time_client.h"
#include "utils.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        ERROR("Usage: time_client [IP]");
        return -1;
    }
    huoguo::net::EventLoop loop;
    huoguo::sample::TimeClient client(&loop, argv[1], 2037);
    client.start();
    return loop.run();
}