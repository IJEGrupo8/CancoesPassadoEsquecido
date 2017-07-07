#include "room.hpp"
#include "scene.hpp"
#include "enemy.hpp"
#include "components/animation.hpp"
#include "components/animationcontroller.hpp"
#include "components/damageEnemy.hpp"
#include "components/follow.hpp"
#include "components/animation.hpp"
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
    AnimationComponent * enemyAnimation = new AnimationComponent(*newEnemy, "ghost.png", 4, 4, 500, 0, 3 ,-1);
    FollowPlayer * moveEnemy = new FollowPlayer(*newEnemy);
    AnimationControllerComponent * animationController = new AnimationControllerComponent(*newEnemy);
    animationController->addAnimation("iddle", *enemyAnimation);
    DamageEnemy * damagePlayer = new DamageEnemy(*newEnemy);
    newEnemy->add_component(*damagePlayer);
    newEnemy->add_component(*animationController);
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
