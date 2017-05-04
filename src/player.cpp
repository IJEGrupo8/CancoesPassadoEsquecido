#include "gameobject.hpp"
#include "player.hpp"
#include "components/text.hpp"
#include "components/image.hpp"
#include "log.h"
#include "vector.hpp"

#define nframes 4

using namespace engine;

bool Player::init()
{
    engine::GameObject::init();
    
    //INFO("x"<<physics.collisionBox.x<<"  y"<<physics.collisionBox.y <<"  w"<<physics.collisionBox.w<< "    h"<< physics.collisionBox.h)
    return true;
}

bool Player::shutdown()
{
    engine::GameObject::shutdown();
    return true;
}

bool Player::draw()
{
    engine::GameObject::draw();

    return true;
}

bool Player::update()
{
    //engine::GameObject::update(force,xFInc,yFSub);
    physics.velocity += physics.aceleration;
    physics.position += physics.velocity;
    
    int collisionAdjust = 30;
    physics.collisionBox.x = physics.position.getX() + collisionAdjust;
    physics.collisionBox.y = physics.position.getY() + collisionAdjust;
    physics.collisionBox.w = w - collisionAdjust;
    physics.collisionBox.h = h - collisionAdjust;

    return true;
}
bool Player::moveDown(){
    // Update Velocity
    int componentX = 0;
    int componentY = 3;

    Vector2D move(componentX,componentY);
    physics.velocity = move;
    // Update Frame
    int xFrame = (((xF/w)+1)%nframes)*w;
    int yFrame = 0*h;

    xF = xFrame;
    yF = yFrame;
}

bool Player::moveUp(){
    // Update Velocity
    int componentX = 0;
    int componentY = -3;

    Vector2D move(componentX,componentY);
    physics.velocity = move;
    // Update Frame
    int xFrame = (((xF/w)+1)%nframes)*w;
    int yFrame = 3*h;

    xF = xFrame;
    yF = yFrame;
}

bool Player::moveLeft(){
    // Update Velocity
    int componentX = -3;
    int componentY = 0;

    Vector2D move(componentX,componentY);
    physics.velocity = move;
    // Update Frame
    int xFrame = (((xF/w)+1)%nframes)*w;
    int yFrame = 1*h;

    xF = xFrame;
    yF = yFrame;
}

bool Player::moveRight(){
    // Update Velocity
    int componentX = 3;
    int componentY = 0;

    Vector2D move(componentX,componentY);
    physics.velocity = move;
    // Update Frame
    int xFrame = (((xF/w)+1)%nframes)*w;
    int yFrame = 2*h;

    xF = xFrame;
    yF = yFrame;
}