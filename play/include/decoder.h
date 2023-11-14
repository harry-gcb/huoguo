#ifndef HUOGUO_PLAY_DECODER_H_
#define HUOGUO_PLAY_DECODER_H_

#include "ffmpeg.h"

namespace huoguo {
namespace play {

class Decoder {
public:
    Decoder();
    ~Decoder();
    int init(int codec_id);
    int open();
    int close();
public:
    AVCodec *m_codec;
    AVCodecParserContext *m_parser;
    AVCodecContext *m_ctx;
};

}
}

#endif // HUOGUO_PLAY_DECODER_H_