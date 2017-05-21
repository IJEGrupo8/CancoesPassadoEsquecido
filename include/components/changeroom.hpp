#ifndef __COMPONENTS_CHANGE_ROOM__
#define __COMPONENTS_CHANGE_ROOM__

#include "components/code.hpp"
#include "gameobject.hpp"

using namespace engine;

class ChangeRoom : public CodeComponent {
public:
	enum class Direction {
        right,
        left,
        top,
        botton
    };
    ChangeRoom(GameObject & game_object, Direction dir)
        : CodeComponent(game_object), direction(dir) {}
        
    ChangeRoom() : CodeComponent() {}

    ~ChangeRoom() {}
    
    virtual bool update();
    virtual bool init();
    GameObject * player;
    Direction direction;
    //Timer timer;

};



#endif