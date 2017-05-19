#include "log.h"
#include "components/follow.hpp"
#include "vector.hpp"
#include "game.hpp"


bool FollowPlayer::init(){
    //timer.startTimer();
    m_game_object->physics.velocity.setY(3);
    

    //player = 


}
bool FollowPlayer::update(){

    player = Game::instance.m_scene->get_game_object("Player1");
    Vector2D pos = player->physics.position;
    m_game_object->physics.velocity = pos - m_game_object->physics.position;
    m_game_object->physics.velocity.normalize();
    //m_game_object->physics.velocity *= 2;
   // INFO("VEL = " << m_game_object->physics.velocity.getX() << "  " << m_game_object->physics.velocity.getY());
    return true;
}