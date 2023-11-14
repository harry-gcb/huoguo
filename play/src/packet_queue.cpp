#include "packet_queue.h"

namespace huoguo {
namespace play {

PacketQueue::PacketQueue()
    : m_pkt_list(nullptr),
      m_nb_packets(0),
      m_size(0),
      m_duration(0),
      m_abort_request(0),
      m_serial(0) {
}

}
}