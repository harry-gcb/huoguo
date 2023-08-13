#ifndef HUOGUO_NET_CALLBACK_H_
#define HUOGUO_NET_CALLBACK_H_

#include <functional>
#include <memory>

namespace huoguo {
namespace net {

class Buffer;
using BufferPtr = std::shared_ptr<Buffer>;
class TcpConnection;
using TcpConnectionPtr = std::shared_ptr<huoguo::net::TcpConnection>;

using ConnectCallback = std::function<void (const TcpConnectionPtr &)>;
using MessageCallback = std::function<void (const TcpConnectionPtr &)>;

void default_connect_callback(const TcpConnectionPtr &conn);
void default_message_callback(const TcpConnectionPtr &conn);

} // namespace net
} // namespace huoguo

#endif // HUOGUO_NET_CALLBACK_H_