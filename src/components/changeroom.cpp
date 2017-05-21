#include "log.h"
#include "components/changeroom.hpp"
#include "vector.hpp"
#include "game.hpp"


bool ChangeRoom::init(){
    //m_game_object->physics.velocity.setY(3);
    INFO("Init changeroom");
    
    return true;
}
bool ChangeRoom::update(){

	
    player = Game::instance.m_scene->get_game_object("Player1");
    //INFO(" X Y" << player )
    if(m_game_object->physics.detectColision(player)){
   		INFO("player is colliding");
    }
    /*Vector2D pos = player->physics.position;
    m_game_object->physics.velocity = pos - m_game_object->physics.position;
    m_game_object->physics.velocity.normalize();*/
    //m_game_object->physics.velocity *= 2;
   // INFO("VEL = " << m_game_object->physics.velocity.getX() << "  " << m_game_object->physics.velocity.getY());
    return true;
}