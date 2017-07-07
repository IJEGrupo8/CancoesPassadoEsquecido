#include "room.hpp"
#include "scene.hpp"
#include "enemy.hpp"
#include "components/animation.hpp"
#include "components/animationcontroller.hpp"
#include "components/damageEnemy.hpp"
#include "components/follow.hpp"
#include "components/animation.hpp"
#include "gameglobals.hpp"
#include "log.h"

using namespace engine;

bool Room::init(){
    return Scene::init();
}

bool Room::update()
{
    return Scene::update();
}

bool Room::draw()
{
    return Scene::draw();
}

bool Room::add_enemy(std::string enemy_id, int x, int y, Player * target, int enemy_life, int enemy_type)
{
    Enemy * newEnemy = new Enemy(enemy_id, x, y, target, enemy_life, enemy_type);
    newEnemy->xF = 0; newEnemy->yF = 0;
   
    std::string spritePath = "";
    if(enemy_type == globals::MAD_ENEMY){
        spritePath = "enemy.png";
    }
    else if(enemy_type == globals::SAD_ENEMY){
        spritePath = "sad_enemy.png";
    }

    //AnimationControllerComponent *enemyController = new AnimationControllerComponent(*newEnemy);

    AnimationComponent *enemyMoveRight = new AnimationComponent(*newEnemy,spritePath,8,4,1000,24,31,-1);
    AnimationComponent *enemyMoveLeft = new AnimationComponent(*newEnemy,"enemyRedLeft.png",8,1,2000,0,7,-1);
    AnimationComponent *enemyMoveDown = new AnimationComponent(*newEnemy,"enemyRedDown.png",4,1,2000,0,3,-1);
    AnimationComponent *enemyMoveUp = new AnimationComponent(*newEnemy,spritePath,6,4,2000,12,15,-1);

    /*enemyController->addAnimation(globals::moveLeft,*enemyMoveLeft);
    enemyController->addAnimation(globals::moveRight,*enemyMoveRight);
    enemyController->addAnimation(globals::moveDown,*enemyMoveDown);
    enemyController->addAnimation(globals::moveUp,*enemyMoveUp);*/
    
    newEnemy->moveRightA = enemyMoveRight;
    newEnemy->moveUpA = enemyMoveUp;
    newEnemy->moveDownA = enemyMoveDown;
    
    newEnemy->moveLeftA = enemyMoveLeft;

    FollowPlayer * moveEnemy = new FollowPlayer(*newEnemy);
    DamageEnemy * damagePlayer = new DamageEnemy(*newEnemy);
    newEnemy->add_component(*damagePlayer);
    newEnemy->add_component(*moveEnemy);

    add_game_object(*newEnemy);
    return true;
}
bool Room::add_room_transition(std::string id_transition, int x, int y, int w, int h, std::string target_room, ChangeRoom::Direction direction){
    GameObject * transition = new GameObject(id_transition, x, y);
    ChangeRoom * changeRoomComponent = new ChangeRoom(*transition, target_room, direction);
    transition->add_component(*changeRoomComponent);
    transition->w = w; transition->h = h;

    add_game_object(*transition);
    return true;
}
