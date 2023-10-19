#ifndef HUOGUO_RTP_RTP_PORTPAIR_H_
#define HUOGUO_RTP_RTP_PORTPAIR_H_

namespace huoguo {
namespace rtp {

class RtpPortPair {
public:
    RtpPortPair(int rtp_port,int rtcp_port);
    ~RtpPortPair();
    int get_rtp_port() const;
    int get_rtcp_port() const;
protected:
    int m_rtp_port = 0;
    int m_rtcp_port = 0;
};

}
}

#endif