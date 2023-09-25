#include "utils_string.h"
#include "sdp.h"
#include <iostream>

namespace huoguo {
namespace sdp {

int Sdp::from_string(const std::string &buffer) {
    std::shared_ptr<SdpMeta> meta = nullptr;
    auto sdp_line = utils::split(buffer, "\r\n");
    if (sdp_line.empty()) {
        auto sdp_line = utils::split(buffer, "\n");
    }
    for (auto &line: sdp_line) {
        // std::cout << line << std::endl;
        if (line.empty()) {
            continue;
        }
        auto pos = line.find_first_of("=");
        if (pos == std::string::npos) {
            return -1;
        }
        std::string key = line.substr(0, pos);
        std::string val = line.substr(pos+1);
        if ("v" == key) { 
            m_session = std::make_shared<SdpSession>();
            meta = m_session; 
        } else if ("m" == key) {
            auto stream = std::make_shared<SdpStream>();
            m_streams.push_back(stream);
            meta = stream;
        }
        meta->set(key, val);
    }
    return 0;
}

std::string Sdp::to_string() {
    std::string sdp;
    if (m_session) sdp.append(m_session->to_string());
    for (auto &stream: m_streams) {
        sdp.append(stream->to_string());
    }
    return sdp;
}

}
}