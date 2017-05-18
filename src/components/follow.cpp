#include "log.h"
#include "components/follow.hpp"
#include "vector.hpp"
#include "game.hpp"


bool FollowPlayer::init(){
    //timer.startTimer();
    m_game_object->physics.velocity.setY(3);
    player = &Game::instance.m_scene->get_game_object("Player1");

    //player = 


}
bool FollowPlayer::update(){
    Vector2D pos = player->physics.position;
    m_game_object->physics.velocity = m_game_object->physics.position+pos;
    m_game_object->physics.velocity *=-1;
    m_game_object->physics.velocity.normalize();
    m_game_object->physics.velocity *= 2;
    return true;
}