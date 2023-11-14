#ifndef HUOGUO_PLAY_PLAYER_H_
#define HUOGUO_PLAY_PLAYER_H_

#include <cstdint>

namespace huoguo {
namespace play {

class Player {
public:
    Player();
    // play control
    int start();
    int pause();
    int stop();
    int seek(long msec);

    void set_video_codec_info();
    void set_audio_codec_info();

    int input_video_data(const uint8_t *data, size_t size);
    int input_audio_data(const uint8_t *data, size_t size);
    int close();
private:
    // Demuxer m_demuxer;
    // Decoder m_decoder;

};

}
}

#endif // HUOGUO_PLAYER_PLAYER_H_