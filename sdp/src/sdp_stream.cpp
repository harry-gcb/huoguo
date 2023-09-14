#include "sdp_stream.h"
#include "utils_string.h"
#include "logger.h"

namespace huoguo {
namespace sdp {

void SdpStream::set(const std::string &key, const std::string &val) {
    if ("m" == key) {
        std::vector<std::string> media = utils::split(val, " ");
        if (media.size() < 4) {
            return;
        }
        m_m_type = media[0];
        m_m_port = media[1];
        m_m_protocol = media[2];
        for (size_t i=3; i<media.size(); ++i) {
            m_m_format.push_back(media[i]);
        }
    } else if ("a" == key) {
        m_attributes.push_back(val);
    } else {
        INFO("%s=%s", key.c_str(), val.c_str());
    }
}

std::string SdpStream::to_string() {
    std::string stream;
    stream.append("m=").append(m_m_type).append(" ")
                        .append(m_m_port).append(" ")
                        .append(m_m_protocol);
    for (auto &format: m_m_format) {
        stream.append(" ").append(format);
    }
    stream.append("\r\n");
    for (auto &attr: m_attributes) {
        stream.append("a=").append(attr).append("\r\n");
    }
    return stream;
}

}
}