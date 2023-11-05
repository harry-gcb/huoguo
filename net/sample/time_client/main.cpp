#include "time_client.h"
#include "utils_logger.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        ErrorL("Usage: time_client [IP]");
        return -1;
    }
    huoguo::net::EventLoop loop;
    huoguo::sample::TimeClient client(&loop, argv[1], 2037);
    client.start();
    return loop.run();
}