#include "rtp_portpool.h"

namespace huoguo {
namespace rtp {

bool RtpPortPool::require_free_port_pair(int &port1, int &port2) {
    for (int port = RTP_MIN_PORT; port < RTP_MAX_PORT; port += 2) {
        if (m_used_port.find(port) == m_used_port.end()) {
            port1 = port;
            port2 = port + 1;
            m_used_port.insert({port1, port2});
            return true;
        }
    }
    return false;

}

void RtpPortPool::release_used_port_pair(int port1, int port2) {
    auto it = m_used_port.find(port1);
    if (it == m_used_port.end()) {
        return;
    }
    m_used_port.erase(it);
}

}
}