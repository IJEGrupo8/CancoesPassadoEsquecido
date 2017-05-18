#ifndef __COMPONENTS_MOVE_SIDE_TO_SIDE__
#define __COMPONENTS_MOVE_SIDE_TO_SIDE__

#include "sdl2include.h"
#include "components/code.hpp"
#include "gameobject.hpp"
#include "timer.hpp"

using namespace engine;

class MoveSSDirectionals : public CodeComponent {
public:
    MoveSSDirectionals(GameObject & game_object)
        : CodeComponent(game_object) {}
        
    MoveSSDirectionals() : CodeComponent() {}

    ~MoveSSDirectionals() {}
    
    virtual bool update();
    virtual bool init();
    Timer timer;
};



#endif
