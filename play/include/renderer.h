#ifndef HUOGUO_PLAY_RENDERER_H_
#define HUOGUO_PLAY_RENDERER_H_

namespace huoguo {
namespace player {

class Renderer {
public:
    void draw(std::shared_ptr<RawData> data);
};

}
}

#endif // HUOGUO_PLAYER_RENDERER_H_