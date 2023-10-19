#include "rtp_portpair.h"
#include "rtp_portpool.h"

namespace huoguo {
namespace rtp {

RtpPortPair::RtpPortPair(int rtp_port, int rtcp_port)
    : m_rtp_port(rtp_port),
      m_rtcp_port(rtcp_port) {
}

RtpPortPair::~RtpPortPair() {
    utils::Singleton<RtpPortPool>::getInstance().release(*this);
}

int RtpPortPair::get_rtp_port() const {
    return m_rtp_port;
}
int RtpPortPair::get_rtcp_port() const {
    return m_rtcp_port;
}

}
}