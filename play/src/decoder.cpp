#include "decoder.h"

namespace huoguo {
namespace play {

Decoder::Decoder()
    : m_codec(nullptr), 
      m_parser(nullptr),
      m_ctx(nullptr) {
}

Decoder::~Decoder() {
    close();
}

int Decoder::init(int codec_id) {
    m_codec = (AVCodec *)avcodec_find_decoder(static_cast<AVCodecID>(codec_id));
    if (m_codec) {
        return -1;
    }
    m_parser = av_parser_init(m_codec->id);
    if (!m_parser) {
        return -1;
    }
    m_ctx = avcodec_alloc_context3(m_codec);
    if (!m_ctx) {
        return -1;
    }
    return 0;
}

int Decoder::open() {

    return avcodec_open2(m_ctx, m_codec, nullptr);
}

int Decoder::close() {
    if (m_parser) {
        av_parser_close(m_parser);
        m_parser = nullptr;
    }
    if (m_ctx) {
        avcodec_free_context(&m_ctx);
        m_ctx = nullptr;
    }
    return 0;
}

}
}