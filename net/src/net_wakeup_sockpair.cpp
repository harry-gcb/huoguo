#ifdef USE_SOCKPAIR_WAKEUP

#include <future>
#include <thread>
#include "net_socket.h"
#include "net_inetaddr.h"
#include "net_wakeup_sockpair.h"

namespace huoguo {
namespace net {

SockPairWakeup::SockPairWakeup() 
    : m_accept_start(false),
      m_acceptor(new Socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)),
      m_connector(new Socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) {
    InetAddr addr(0, LOCALHOST, true);
    m_acceptor->bind(addr);
    m_acceptor->listen(1);

    struct sockaddr_in accept_addr = { 0 };
    struct sockaddr_in connect_addr = { 0 };
    int accept_size = sizeof(accept_addr);
	int connect_size = sizeof(connect_addr);
    
	if (getsockname(m_acceptor->get_fd(), (struct sockaddr *) &connect_addr, &connect_size) == -1)
    {
        ErrorL("getsockname error");
    }
    int ret = m_connector->connect((struct sockaddr *)&connect_addr, connect_size);
    m_reader = m_acceptor->accept((struct sockaddr *)&accept_addr, &accept_size);
    InfoL("connect ret=%d", ret);
#if 0
    m_accept_thread = std::thread([this]{
        while (!m_reader) {
            m_accept_start = true;
            m_accetp_cv.notify_one();
            m_reader = m_acceptor->accept();
            if (!m_reader) {
                ErrorL("accept error");
                continue;
            }
        }
    });
    m_accept_thread.detach();
    while (!m_reader) {
        //using namespace std::chrono_literals;
        //std::unique_lock lock(m_accept_mutex);
        //m_accetp_cv.wait_for(lock, 200ms, [this] {
        //    return m_accept_start;
        //});
        InfoL("connect");
        
        ErrorL("ret=%d", ret);
    }
#endif
}

int SockPairWakeup::get_fd() {
    return m_reader->get_fd();
}

Channel *SockPairWakeup::get_channel() {
    return m_reader->get_channel();
}

void SockPairWakeup::set_channel(Channel *channel) {
    m_reader->set_channel(channel);
}

int SockPairWakeup::read(char *data, int len) {
    return m_reader->read(data, len);
}

int SockPairWakeup::write(const char *data, int len) {
    return m_connector->write(data, len);
}

}
}

#endif