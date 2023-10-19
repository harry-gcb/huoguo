#ifndef HUOGUO_RTP_RTP_PORTPOOL_H_
#define HUOGUO_RTP_RTP_PORTPOOL_H_

#include <map>
#include "utils.h"
#include "rtp_portpair.h"

namespace huoguo {
namespace rtp {

#define RTP_MIN_PORT 10000
#define RTP_MAX_PORT 40000
class RtpPortPool {
public:
    std::shared_ptr<RtpPortPair> require() {
        for (int port = RTP_MIN_PORT; port < RTP_MAX_PORT; port += 2) {
            if (m_used_port.find(port) == m_used_port.end()) {
                auto port_pair = std::make_shared<RtpPortPair>(port, port + 1);
                m_used_port.insert({port, port + 1});
                return port_pair;
            }
        }
        return nullptr;
    }
    void release(RtpPortPair port_pair) {
        auto it = m_used_port.find(port_pair.get_rtp_port());
        if (it == m_used_port.end()) {
            return;
        }
        m_used_port.erase(it);
    }
private:
    int m_min_port = RTP_MIN_PORT;
    std::map<int, int> m_used_port;
};

} // namespace rtp
} // namespace huoguo

#endif // HUOGUO_RTP_RTP_PORTPOOL_H_