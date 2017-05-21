#ifndef __COMPONENTS_FOLLOW_PLAYER__
#define __COMPONENTS_FOLLOW_PLAYER__


#include "components/code.hpp"
#include "gameobject.hpp"

using namespace engine;

class FollowPlayer : public CodeComponent {
public:
    FollowPlayer(GameObject & game_object)
        : CodeComponent(game_object) {}
        
    FollowPlayer() : CodeComponent() {}

    ~FollowPlayer() {}
    
    virtual bool update();
    virtual bool init();
    GameObject * player;
    //Timer timer;

};



#endif
