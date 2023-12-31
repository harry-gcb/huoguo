#ifndef HUOGUO_NET_CALLBACK_H_
#define HUOGUO_NET_CALLBACK_H_

#include <functional>
#include <memory>

namespace huoguo {
namespace net {

class InetAddr;
class TcpConnection;
class UdpConnection;
using ConnectCallback = std::function<void (const std::shared_ptr<TcpConnection> &)>;
using SegmentCallback = std::function<void (const std::shared_ptr<TcpConnection> &, const uint8_t *, size_t)>;
using CloseCallback = std::function<void (const std::shared_ptr<TcpConnection> &)>;
using DatagramCallback = std::function<void (const std::shared_ptr<UdpConnection> &, const InetAddr &, const uint8_t *, size_t)>;


void default_connect_callback(const std::shared_ptr<TcpConnection> conn);
void default_message_callback(const std::shared_ptr<TcpConnection> conn, const uint8_t *data, size_t size);

} // namespace net
} // namespace huoguo

#endif // HUOGUO_NET_CALLBACK_H_