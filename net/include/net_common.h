#ifndef HUOGUO_NET_COMMON_H_
#define HUOGUO_NET_COMMON_H_

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment (lib, "ws2_32.lib") 

class Win32NetInitializer {
public:
    Win32NetInitializer() {
        WSADATA wsaData;
        WSAStartup( MAKEWORD(2, 2), &wsaData);
    }
    ~Win32NetInitializer() {
        WSACleanup();
    }
};

static Win32NetInitializer win32NetInitializer;

namespace huoguo {
namespace net {

using socklen_t=int;
using sa_family_t = unsigned short;

#define LOCALHOST "127.0.0.1"

}
}

#else
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#endif



#endif // HUOGUO_NET_INET_SOCK_H_