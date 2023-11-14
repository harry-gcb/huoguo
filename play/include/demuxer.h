#ifndef HUOGUO_PLAY_DEMUXER_H_
#define HUOGUO_PLAY_DEMUXER_H_

namespace huoguo {
namespace player {

class Demuxer {
public:
    std::shared_ptr<Frame> input_packet(std::shared_ptr<Packet> packet);
};

}
}

#endif // HUOGUO_PLAYER_DEMUXER_H_