#ifndef __COMPONENTS_MOVE_SIDE_TO_SIDE__
#define __COMPONENTS_MOVE_SIDE_TO_SIDE__

#include "sdl2include.h"
#include "components/code.hpp"
#include "player.hpp"
using namespace engine;

class MoveSSDirectionals : public CodeComponent {
public:
    MoveSSDirectionals(Player & game_object)
        : CodeComponent(game_object) {}
        
    MoveSSDirectionals() : CodeComponent() {}

    ~MoveSSDirectionals() {}

    virtual bool update();

};



#endif
