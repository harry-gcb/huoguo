#include "time_server.h"

int main(int argc, char *argv[]) {
    huoguo::net::EventLoop loop;
    huoguo::sample::TimeServer server(&loop, 2037);
    server.start();
    return loop.run();
}