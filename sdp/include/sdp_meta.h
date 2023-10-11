#ifndef HUOGUO_SDP_META_H_
#define HUOGUO_SDP_META_H_

#include <string>

namespace huoguo {
namespace sdp {

class SdpMeta {
public:
    virtual void set(const std::string &key, const std::string &val) = 0;
    // virtual void from_string(const std::string &buffer) = 0;
    virtual std::string to_string() = 0;
};

}
}

#endif // HUOGUO_SDP_SDP_META_H_