#include "sdp_session.h"
#include "utils.h"

namespace huoguo {
namespace sdp {

void SdpSession::set(const std::string &key, const std::string &val) {
    if ("v" == key) {
        m_v_version = val;
    } else if ("o" == key) {
        std::vector<std::string> origion = utils::split(val, " ");
        if (origion.size() < 6) {
            return;
        }
        m_o_username = origion[0];
        m_o_sessionid = origion[1];
        m_o_version = origion[2];
        m_o_network_type = origion[3];
        m_o_address_type = origion[4];
        m_o_address = origion[5];
    } else if ("s" == key) {
        m_s_sessionname = val;
    } else if ("c" == key) {
        std::vector<std::string> connection = utils::split(val, " ");
        if (connection.size() < 3) {
            return;
        }
        m_c_network_type = connection[0];
        m_c_address_type = connection[1];
        m_c_address = connection[2];
    } else if ("t" == key) {
        std::vector<std::string> active_time = utils::split(val, " ");
        if (active_time.size() < 2) {
            return;
        }
        m_t_start_time = active_time[0];
        m_t_stop_time = active_time[1];
    } else if ("a" == key) {
        m_attributes.push_back(val);
    } else {
        INFO("%s=%s", key.c_str(), val.c_str());
    }
}

std::string SdpSession::to_string() {
    std::string session;
    session.append("v=").append(m_v_version).append("\r\n");
    session.append("o=").append(m_o_username).append(" ")
                        .append(m_o_sessionid).append(" ")
                        .append(m_o_version).append(" ")
                        .append(m_o_network_type).append(" ")
                        .append(m_o_address_type).append(" ")
                        .append(m_o_address).append("\r\n");
    session.append("s=").append(m_s_sessionname).append("\r\n");
    session.append("c=").append(m_c_network_type).append(" ")
                        .append(m_c_address_type).append(" ")
                        .append(m_c_address).append("\r\n");
    session.append("t=").append(m_t_start_time).append(" ")
                        .append(m_t_stop_time).append("\r\n");
    for (auto &attr: m_attributes) {
        session.append("a=").append(attr).append("\r\n");
    }
    return session;
}

}
}

