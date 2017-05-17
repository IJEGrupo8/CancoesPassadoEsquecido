#ifndef __ENGINE_COMPONENTS_CODE__
#define __ENGINE_COMPONENTS_CODE__

#include "sdl2include.h"
#include "components/component.hpp"

namespace engine {

class CodeComponent : public Component {
public:
    CodeComponent(GameObject & game_object)
        : Component(game_object) {}

    CodeComponent() : Component() {}

    ~CodeComponent() {}

    virtual bool update(){ return true;}


protected:

};

}

#endif
