#ifndef __COMPONENTS_DAMAGE_ENEMY__
#define __COMPONENTS_DAMAGE_ENEMY__

#include "components/code.hpp"
#include "gameobject.hpp"
#include "player.hpp"

using namespace engine;

class DamageEnemy : public CodeComponent {
public:
    DamageEnemy(GameObject & game_object)
        : CodeComponent(game_object){}
        
    DamageEnemy() : CodeComponent() {}

    ~DamageEnemy() {}
    
    virtual bool update();
    virtual bool init();
    Player * player;

};

#endif