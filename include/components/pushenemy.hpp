#ifndef __COMPONENTS_PUSHENEMY_PLAYER__
#define __COMPONENTS_PUSHENEMY_PLAYER__


#include "components/code.hpp"
#include "gameobject.hpp"

using namespace engine;

class PushEnemy : public CodeComponent {
public:
    PushEnemy(GameObject & game_object)
        : CodeComponent(game_object) {}
        
    PushEnemy() : CodeComponent() {}

    ~PushEnemy() {}
    
    virtual bool update();
    virtual bool init();
};

#endif
