#include "gameobject.hpp"
#include "physics.hpp"
#include "log.h"

using namespace engine;

Vector2D null(0,0);
bool PhysicsComponent::detectColision( GameObject* obj)
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    
    //Calculate the sides of rect A
    leftA = collisionBox.x;
    rightA = collisionBox.x + collisionBox.w;
    topA = collisionBox.y;
    bottomA = collisionBox.y + collisionBox.h;
    //Calculate the sides of rect B
    leftB = obj->physics.collisionBox.x;
    rightB = obj->physics.collisionBox.x + obj->physics.collisionBox.w;
    topB = obj->physics.collisionBox.y;
    bottomB = obj->physics.collisionBox.y + obj->physics.collisionBox.h;
    //If any of the sides from A are outside of B
    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}
/*bool Scene::verifyColision(GameObject* ob)
{
    bool result;
    for (auto id_obj: m_objects)
    {
        if(ob != id_obj.second){
            result = isColliding(ob,id_obj.second);
            if(result){
                printf("colliding with %s\n",id_obj.second->name().c_str());
            }
        }
    }

    return result;
}*/