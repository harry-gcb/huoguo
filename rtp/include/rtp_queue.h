#ifndef HUOGUO_RTP_QUEUE_H_
#define HUOGUO_RTP_QUEUE_H_

#include "rtp_packet.h"
#include <memory>

namespace huoguo {
namespace rtp {

class RtpQueue {
public:
    int push(std::shared_ptr<RtpPacket> packet);
};

}
}

#endif // HUOGUO_RTP_QUEUE_H_