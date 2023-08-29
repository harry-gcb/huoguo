#include "rtsp.h"

namespace huoguo {
namespace app {

Rtsp::Rtsp(const std::string &url) 
    : m_client(&m_loop, url),
      m_stop(false) {
    // m_client.set_on_options(std::bind(&Rtsp::on_options, this, std::placeholders::_1));


}

void Rtsp::start() {
    m_client.start();
    m_thread = std::thread(std::bind(&Rtsp::run, this));
}

void Rtsp::stop() {
    m_stop = true;
    m_loop.active_read_event();
}

void Rtsp::run() {
    while (!m_stop) {
        m_loop.run();
    }
}

}
}
