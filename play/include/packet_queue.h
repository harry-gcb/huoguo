#ifndef HUOGUO_PLAY_PACKET_QUEUE_H_
#define HUOGUO_PLAY_PACKET_QUEUE_H_

#include <mutex>
#include <condition_variable>
#include "ffmpeg.h"

namespace huoguo {
namespace play {

#if 0
typedef struct MyAVPacketList {
    AVPacket *pkt;
    int serial;
} MyAVPacketList;

typedef struct PacketQueue {
    AVFifo *pkt_list;
    int nb_packets;
    int size;
    int64_t duration;
    int abort_request;
    int serial;
    SDL_mutex *mutex;
    SDL_cond *cond;
} PacketQueue;
#endif

class PacketQueue {
public:
    PacketQueue();
public:
    AVFifo *m_pkt_list;
    int m_nb_packets;
    int m_size;
    int64_t m_duration;
    int m_abort_request;
    int m_serial;

    std::mutex mutex;
    std::condition_variable m_cond;

};

}
}

#endif // HUOGUO_PLAY_PACKET_QUEUE_H_