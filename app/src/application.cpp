#include "application.h"
#include "option.h"
#include "config.h"
#include "logger.h"
#include "strutils.h"
#include "rtsp.h"

namespace huoguo {
namespace app {

Application::Application(int argc, char *argv[]) {
    init_option(argc, argv);
    init_logs();
}

static void pull_rtsp(const std::string &url) {
    auto rtsp = std::make_shared<huoguo::app::Rtsp>(url);
    rtsp->start();
}

int Application::run() {
    if (OPTION.is_exists("h") || OPTION.is_exists("help")) {
        OPTION.usage();
        return 0;
    }
    if (OPTION.is_exists("pull")) {
        std::string url = OPTION.get("pull");
        if (huoguo::utils::starts_with(url, "rtsp")) {
            pull_rtsp(url);
        }
    }
    while (!m_stop) {
        using namespace std::literals::chrono_literals;
        std::unique_lock<std::mutex> lock(m_mutex);
        m_cv.wait_for(lock, 1s);
    }
    return 0;
}

int Application::init_option(int argc, char *argv[]) {
    OPTION.add("h", "help", "help info")
          .add("f", "", "config file")
          .add("", "pull", "stream url")
          .add("", "transport", "transport protocol");
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
    config.filename = CONFIG.get("LOG", "filename", "huoguo");
    config.suffix = CONFIG.get("LOG", "suffix", "txt");
    config.enable_color = CONFIG.get("LOG", "color", false);
    config.level = CONFIG.get("LOG", "level", "info");
    return LOGGER.init(config);
}

}
}