#ifndef __COMPONENTS_CHEST__
#define __COMPONENTS_CHEST__


#include "components/code.hpp"
#include "gameobject.hpp"

using namespace engine;

class ChestComponent : public CodeComponent {
public:
    ChestComponent(GameObject & game_object)
        : CodeComponent(game_object) {}
        
    ChestComponent() : CodeComponent() {}

    ~ChestComponent() {}
    
    virtual bool update();
    virtual bool init();
    GameObject * player;
    //Timer timer;

};

#endif