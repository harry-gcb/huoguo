#ifndef HUOGUO_SDP_SDP_SESSION_H_
#define HUOGUO_SDP_SDP_SESSION_H_

#include "sdp_meta.h"
#include <vector>

namespace huoguo {
namespace sdp {

class SdpSession : public SdpMeta {
public:
    virtual void set(const std::string &key, const std::string &val) override;

    virtual std::string to_string() override;
private:
    std::string m_v_version;

    std::string m_o_username;
    std::string m_o_sessionid;
    std::string m_o_version;
    std::string m_o_network_type;
    std::string m_o_address_type;
    std::string m_o_address;

    std::string m_s_sessionname;

    std::string m_c_network_type;
    std::string m_c_address_type;
    std::string m_c_address;

    std::string m_t_start_time;
    std::string m_t_stop_time;

    std::vector<std::string> m_attributes;
};

}
}

#endif // HUOGUO_SDP_SDP_SESSION_H_