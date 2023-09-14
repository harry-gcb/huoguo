#ifndef HUOGUO_SDP_SDP_H_
#define HUOGUO_SDP_SDP_H_

#include <string>
#include <vector>
#include <memory>

#include "sdp_session.h"
#include "sdp_stream.h"

namespace huoguo {
namespace sdp {

class Sdp {
public:
    int from_string(const std::string &buffer);
    std::string to_string();
private:
    std::shared_ptr<SdpSession> m_session;
    std::vector<std::shared_ptr<SdpStream>> m_streams;
};

}
}

#endif // HUOGUO_SDP_SDP_H_