#include "utils_config.h"
#include "utils_option.h"
#include "utils_logger.h"

#include "application.h"
// #include "utils.h"
#include "rtsp_puller.h"
#include "rtsp_player.h"

#include <iostream>

namespace huoguo {
namespace app {

Application::Application(int argc, char *argv[]) {
    init_option(argc, argv);
    init_config();
    init_logs();
}

int Application::run() {
    if (OPTION.is_exists("h") || OPTION.is_exists("help")) {
        OPTION.usage();
        return 0;
    }
    net::EventLoop m_loop;
    auto rtsp = std::make_shared<RtspPlayer>(&m_loop);
    if (OPTION.is_exists("play")) {
        rtsp->pull(OPTION.get("play"));
    }
    return m_loop.run();
    
    // while (!m_stop) {
    //     using namespace std::literals::chrono_literals;
    //     std::unique_lock<std::mutex> lock(m_mutex);
    //     m_cv.wait_for(lock, 1s);
    // }
    // return 0;
}

int Application::init_option(int argc, char *argv[]) {
    OPTION.add("h", "help", "help info")
          .add("f", "", "config file", true)
          .add("", "pull", "remote source url", true)
          .add("", "push", "remote target url", true)
          .add("", "from", "local source file", true)
          .add("", "to", "local target file", true)
          .add("", "transport", "transport protocol", true);
    return OPTION.init(argc, argv);
}

void Application::init_config() {
    if (OPTION.is_exists("f")) {
        std::string config = OPTION.get("f");
        CONFIG.init(config);
    }
}

void Application::init_logs() {
    huoguo::utils::LogConfig config;
    config.logdir = CONFIG.get("LOG", "logdir", "logs");
    // config.filename = CONFIG.get("LOG", "filename", "huoguo");
    config.suffix = CONFIG.get("LOG", "suffix", "txt");
    config.enable_color = CONFIG.get("LOG", "color", false);
    config.level = CONFIG.get("LOG", "level", "debug");
    config.enable_fileline = CONFIG.get("LOG", "fileline", false);
    config.enable_function = CONFIG.get("LOG", "function", false);
    return LOGGER.init(config);
}

}
}