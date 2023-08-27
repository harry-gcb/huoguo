#include "pipe2_wakeup.h"
#include "logger.h"
#include "socket.h"
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>


namespace huoguo {
namespace net {

Pipe2Wakeup::Pipe2Wakeup() {
    int fd[2] = { 0 };
    int ret = pipe2(fd, O_NONBLOCK|O_CLOEXEC);
    if (ret < 0) {
        ERROR("pipe2 failed, ret=%d, errno=%d", ret, errno);
    }
    m_pipe_0= std::make_shared<Socket>(fd[0]);
    m_pipe_1= std::make_shared<Socket>(fd[1]);
}

int Pipe2Wakeup::get_fd() {
    return m_pipe_0->get_fd();
}

Channel *Pipe2Wakeup::get_channel() {
    return m_pipe_0->get_channel();
}
void Pipe2Wakeup::set_channel(Channel *channel) {
    m_pipe_0->set_channel(channel);
}

int Pipe2Wakeup::read(void *data, int len) {
    return m_pipe_0->read(data, len);
}

int Pipe2Wakeup::write(const void *data, int len) {
    return m_pipe_1->write(data, len);
}

}
}