#ifndef __ENGINE_COMPONENTS_PHYSICS__
#define __ENGINE_COMPONENTS_PHYSICS__

#include <string>
#include <utility>
#include <vector>


#include "sdl2include.h"
#include "vector.hpp"

namespace engine {

class PhysicsComponent {
public:
	 class collision {
        public:
        bool left;
        bool right;
        bool up;
        bool down;
    };

    PhysicsComponent(GameObject & _game_object, int _x, int _y)
        : game_object(&_game_object),collisionBox({0,0,0,0}),block(false),
        position(_x,_y),velocity(0,0),aceleration(0,0),collisionObj(0,0) {}

    ~PhysicsComponent() {}

    bool detectColision(GameObject* obj);
    
    GameObject * game_object;
    SDL_Rect collisionBox;
    bool block;
    Vector2D position;
    Vector2D velocity;
    Vector2D aceleration;
    Vector2D collisionObj;
    std::vector<collision> collisions;   
};

}

#endif
