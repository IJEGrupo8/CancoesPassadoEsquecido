#ifndef __COMPONENTS_CHANGE_ROOM__
#define __COMPONENTS_CHANGE_ROOM__

#include "components/code.hpp"
#include "gameobject.hpp"

using namespace engine;

class ChangeRoom : public CodeComponent {
public:
    enum class Direction {
        Right,
        Left,
        Top,
        Botton
    };
    ChangeRoom(GameObject & game_object, std::string room, Direction direction)
        : CodeComponent(game_object), room_name(room), dir(direction){}
        
    ChangeRoom() : CodeComponent() {}

    ~ChangeRoom() {}
    
    virtual bool update();
    virtual bool init();
    GameObject * player;
    std::string room_name;
    Direction dir;
    //Timer timer;

};



#endif