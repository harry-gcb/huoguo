#include "rtsp_session.h"

namespace huoguo {
namespace rtsp {

RtspSession::RtspSession(std::shared_ptr<net::TcpConnection> conn)
    : m_trace_id(conn->get_trace_id()) {
    conn->set_message_callback(std::bind(&RtspSession::on_message, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

void RtspSession::on_message(std::shared_ptr<net::TcpConnection> conn, const uint8_t *data, size_t len) {
    
}

}
}