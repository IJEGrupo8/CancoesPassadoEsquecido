#ifndef __ENGINE_COMPONENTS_AUDIO__
#define __ENGINE_COMPONENTS_AUDIO__

#include <string>
#include <utility>

#include "sdl2include.h"

#include "components/component.hpp"

namespace engine {

class AudioComponent : public Component {
public:
    AudioComponent(GameObject & game_object, std::string path)
        : Component(game_object), m_path(path) {}

    ~AudioComponent() {}

    bool init();
    bool shutdown();
    void play();


private:
    std::string m_path;

    Mix_Chunk *sound = NULL;

};

}

#endif
