#ifndef HUOGUO_RTP_RTP_CALLBACK_H_
#define HUOGUO_RTP_RTP_CALLBACK_H_

#include <functional>
#include <memory>

namespace huoguo {
namespace rtp {

class RtpSession;
class RtpPacket;
using RtpPacketCallback = std::function<void(const std::shared_ptr<RtpSession> &, const std::shared_ptr<RtpPacket> &)>;

}
}

#endif // HUOGUO_RTP_RTP_CALLBACK_H_