#ifndef HUOGUO_RTP_RTP_PORTPOOL_H_
#define HUOGUO_RTP_RTP_PORTPOOL_H_

#include <map>
#include "singleton.h"

namespace huoguo {
namespace rtp {

#define RTP_MIN_PORT 10000
#define RTP_MAX_PORT 40000

class RtpPortPool {
    friend class utils::Singleton<RtpPortPool>;
public:
    bool require_free_port_pair(int &port1, int &port2);
    void release_used_port_pair(int port1, int port2);
private:
    int m_min_port = RTP_MIN_PORT;
    std::map<int, int> m_used_port;
};

} // namespace rtp
} // namespace huoguo

#endif // HUOGUO_RTP_RTP_PORTPOOL_H_