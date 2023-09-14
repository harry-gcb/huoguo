#include "sdp.h"
#include <gtest/gtest.h>

namespace huoguo {
namespace sdp {

TEST(sdp, parse) {
    const std::string buffer = 
        "v=0\r\n"
        "o=- 2252075541 2252075541 IN IP4 0.0.0.0\r\n"
        "s=Media Server\r\n"
        "c=IN IP4 0.0.0.0\r\n"
        "t=0 0\r\n"
        "a=control:*\r\n"
        "a=packetization-supported:DH\r\n"
        "a=rtppayload-supported:DH\r\n"
        "a=range:npt=now-\r\n"
        "m=video 0 RTP/AVP 96\r\n"
        "a=control:trackID=0\r\n"
        "a=framerate:10.000000\r\n"
        "a=rtpmap:96 H264/90000\r\n"
        "a=fmtp:96 packetization-mode=1;profile-level-id=64001F;sprop-parameter-sets=Z2QAH62EAQwgCGEAQwgCGEAQwgCEK1AoAt03AQEBAgA=,aO48sAA=\r\n"
        "a=recvonly\r\n"
        "m=audio 0 RTP/AVP 97\r\n"
        "a=control:trackID=1\r\n"
        "a=rtpmap:97 MPEG4-GENERIC/16000\r\n"
        "a=fmtp:97 streamtype=5;profile-level-id=1;mode=AAC-hbr;sizelength=13;indexlength=3;indexdeltalength=3;config=1408\r\n"
        "a=recvonly\r\n";
    Sdp sdp;
    int ret = sdp.from_string(buffer);
    EXPECT_EQ(ret, 0);

    EXPECT_EQ(buffer, sdp.to_string());
    // std::cout << buffer << std::endl;
    // std::cout << sdp.to_string() << std::endl;
}



} // namespace utils
} // namespace huoguo



