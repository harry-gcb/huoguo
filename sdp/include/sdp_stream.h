#ifndef HUOGUO_SDP_SDP_STREAM_H_
#define HUOGUO_SDP_SDP_STREAM_H_

#include "sdp_meta.h"
#include <vector>

namespace huoguo {
namespace sdp {

class SdpStream : public SdpMeta {
public:
    virtual void set(const std::string &key, const std::string &val) override;
    virtual std::string to_string() override;
private:
    std::string m_m_type;
    std::string m_m_port;
    std::string m_m_protocol;
    std::vector<std::string> m_m_format;
    
    std::vector<std::string> m_attributes;

};

}
}

#endif // HUOGUO_SDP_SDP_STREAM_H_