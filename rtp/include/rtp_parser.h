#ifndef HUOGUO_RTP_PARSER_H_
#define HUOGUO_RTP_PARSER_H_

#include <memory>
#include "rtp_packet.h"

namespace huoguo {
namespace rtp {

class RtpParser {
public:
    std::shared_ptr<RtpPacket> parse(const uint8_t *data, size_t size);
};

}
}

#endif // HUOGUO_RTP_PARSER_H_