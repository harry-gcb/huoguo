#include <cstring>
#include <string_view>
#include "rtsp_url.h"
#include "logger.h"

namespace huoguo {
namespace rtsp {

RtspURL::RtspURL(const std::string &url)
    : m_url(url) {
    if (!parse(url)) {
        ERROR("rtsp url format is error: %s", url.c_str());
    }
    m_url = url;
}

bool RtspURL::parse(const std::string &url) {
    // parse protocol
    std::string_view view(url);
    if (view.starts_with("rtsps://")) {
        m_protocol = "RTSPS";
        view.remove_prefix(strlen("rtsps://"));
    } else if (view.starts_with("rtsp://")) {
        view.remove_prefix(strlen("rtsp://"));
        m_protocol = "RTSP";
    } else {
        return false;
    }
    size_t pos = view.find_last_of("@");
    if (pos != std::string_view::npos) {
        m_auth = view.substr(0, pos);
        view.remove_prefix(m_auth.length() + 1);
    }
    std::string_view address;
    if ((pos = view.find_first_of("/")) != std::string_view::npos) {
        address = view.substr(0, pos);
    } else if ((pos = view.find_first_of("?")) != std::string_view::npos) {
        address = view.substr(0, pos);
    } else {
        address = view;
    }
    view.remove_prefix(address.length());
    if (address.empty()) {
        return false;
    }
    std::string port = "554";
    pos = address.find_first_of(":");
    if (pos != std::string_view::npos) {
        m_ip = address.substr(0, pos);
        if (pos + 1 < address.length()) {
            port = address.substr(pos + 1, address.length() - pos - 1);
        }
    } else {
        m_ip = address;
    }
    m_port = std::atoi(port.c_str());

    if (view.empty()) {
        return true;
    }
    pos = view.find_first_of("?");
    if (pos != std::string_view::npos) {
        m_path = view.substr(0, pos);
        if (pos + 1 < view.length()) {
            m_params = view.substr(pos + 1, view.length() - pos - 1);
        }
    } else {
        m_path = view;
    }
    m_url = url;
    return true;
}

std::string RtspURL::get_ip() const {
    return m_ip;
}

uint16_t RtspURL::get_port() const {
    return m_port;
}


}
}