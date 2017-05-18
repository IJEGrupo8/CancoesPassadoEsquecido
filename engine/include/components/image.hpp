#ifndef __ENGINE_COMPONENTS_IMAGE__
#define __ENGINE_COMPONENTS_IMAGE__

#include <string>
#include <utility>

#include "sdl2include.h"

#include "components/component.hpp"

namespace engine {

class ImageComponent : public Component {
public:
    ImageComponent(GameObject & game_object, std::string path,int m_i, int m_j)
        : Component(game_object), m_path(path), i(m_i), j(m_j) {}

    ImageComponent() : Component() {}

    ~ImageComponent() {}

    virtual bool init();
    virtual bool shutdown();
    virtual void draw();

protected:
    std::string m_path;
    SDL_Texture * m_texture;
    int i,j;

};

}

#endif
