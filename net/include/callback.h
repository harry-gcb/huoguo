#ifndef HUOGUO_NET_CALLBACK_H_
#define HUOGUO_NET_CALLBACK_H_

#include <functional>
#include <memory>

namespace huoguo {
namespace net {

class TcpConnection;
using ConnectCallback = std::function<void (std::shared_ptr<TcpConnection>)>;
using MessageCallback = std::function<void (std::shared_ptr<TcpConnection> , const uint8_t *data, int len)>;
using CloseCallback = std::function<void (std::shared_ptr<TcpConnection>)>;

void default_connect_callback(std::shared_ptr<TcpConnection> conn);
void default_message_callback(std::shared_ptr<TcpConnection> conn, const uint8_t *data, size_t len);

} // namespace net
} // namespace huoguo

#endif // HUOGUO_NET_CALLBACK_H_