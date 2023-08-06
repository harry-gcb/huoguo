#include <iostream>
#include "logger.h"
#include "config.h"

static void init_logs() {
    huoguo::utils::LogConfig config;
    config.logdir = CONFIG.get("LOG", "logdir", "logs");
    config.filename = CONFIG.get("LOG", "filename", "huoguo");
    config.suffix = CONFIG.get("LOG", "suffix", "txt");
    config.enable_color = CONFIG.get("LOG", "color", false);
    config.level = CONFIG.get("LOG", "level", "info");
    LOGGER.init(config);
}

int main(int argc, char **argv) {

    CONFIG.init(argv[1]);
    init_logs();

    // while (true) {
    //     std::string hello;
    //     std::cin >> hello;
    // }
    LOGGER.set_level(TRACE_LEVEL);
    LOG(FATAL, "this is a fatal log:");
    LOG(ERROR, "this is a error log");
    LOG(WARN, "this is a warn log");
    LOG(INFO, "this is a info log");
    LOG(DEBUG, "this is a debug log");
    LOG(TRACE, "this is a trace log");
    // LOGGER.set_filename("huoguo.log");
    // LOGGER.set_filename("huoguo2.log");
    // LOGGER.set_filename("huoguo3.log");
    FATAL("this is a fatal log");
    ERROR("this is a error log");
    WARN("this is a warn log");
    INFO("this is a info log");
    DEBUG("this is a debug log");
    TRACE("this is a trace log");
    while (true) {
        std::string hello;
        std::cin >> hello;
    }
    return 0;
}