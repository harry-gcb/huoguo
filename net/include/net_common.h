#ifndef HUOGUO_NET_COMMON_H_
#define HUOGUO_NET_COMMON_H_

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment (lib, "ws2_32.lib") 

namespace huoguo {
namespace net {

using socklen_t=int;
using sa_family_t = unsigned short;

}
}

#else
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#endif



#endif // HUOGUO_NET_INET_SOCK_H_