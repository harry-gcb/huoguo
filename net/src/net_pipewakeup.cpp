#ifdef NET_MACOS
#include <fcntl.h>
#include <errno.h>
#include "utils.h"
#include "net_pipewakeup.h"

namespace huoguo {
namespace net {

PipeWakeup::PipeWakeup() {
    int fd[2] = { 0 };
    int ret = pipe(fd);
    if (ret < 0) {
        ERROR("pipe2 failed, ret=%d, errno=%d", ret, errno);
    }
    m_pipe_0= std::make_shared<Socket>(fd[0]);
    m_pipe_1= std::make_shared<Socket>(fd[1]);
}

int PipeWakeup::get_fd() {
    return m_pipe_0->get_fd();
}

Channel *PipeWakeup::get_channel() {
    return m_pipe_0->get_channel();
}
void PipeWakeup::set_channel(Channel *channel) {
    m_pipe_0->set_channel(channel);
}

int PipeWakeup::read(void *data, int len) {
    return m_pipe_0->read(data, len);
}

int PipeWakeup::write(const void *data, int len) {
    return m_pipe_1->write(data, len);
}

}
}

#endif