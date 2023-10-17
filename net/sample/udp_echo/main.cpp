#include "echo_server.h"
#include "echo_client.h"
#include <string>

static void init_option(int argc, char *argv[]) {
    OPTION.add("h", "help", "help info").
           add("", "server", "run as echo server").
           add("", "client", "run as echo client").
           add("", "host", "host address", true).
           add("", "port", "host port", true).
           add("", "echo", "echo string", true).
           add("", "count", "echo count", true);
    OPTION.init(argc, argv);
}

int main(int argc, char *argv[]) {
    init_option(argc, argv);
    huoguo::net::EventLoop loop;
    std::string host = OPTION.get("host");
    std::string port = OPTION.get("port");
    if (port.empty()) {
        OPTION.usage();
        return -1;
    }
    if (OPTION.is_exists("client")) {
        std::string echo = OPTION.get("echo");
        std::string count = OPTION.get("count");
        huoguo::sample::EchoClient client(&loop, host, std::atoi(port.c_str()), echo, std::atoi(count.c_str()));
        client.start();
        return loop.run();
    } else {
        huoguo::sample::EchoServer server(&loop, host, std::atoi(port.c_str()));
        server.start();
        return loop.run();
    }
}