#include "udp_client.h"

namespace huoguo {
namespace net {

UdpClient::UdpClient(EventLoop *loop, const InetAddr &addr, const std::string &name)
    : m_loop(loop) {

}

}
}