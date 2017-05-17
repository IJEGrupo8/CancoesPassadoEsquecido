#ifndef __COMPONENTS_MOVE__
#define __COMPONENTS_MOVE__

#include "sdl2include.h"
#include "components/code.hpp"
#include "player.hpp"
using namespace engine;

class MoveDirectionals : public CodeComponent {
public:
    MoveDirectionals(Player & game_object)
        : CodeComponent(game_object) {}
        
    MoveDirectionals() : CodeComponent() {}

    ~MoveDirectionals() {}

    virtual bool update();

};



#endif
