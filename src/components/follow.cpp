#include "log.h"
#include "components/follow.hpp"
#include "vector.hpp"
#include "game.hpp"
#include "enemy.hpp"


bool FollowPlayer::init(){
    m_game_object->physics.velocity.setY(3);
    return true;
}
bool FollowPlayer::update(){
		auto enemy = (dynamic_cast<Enemy*>(m_game_object));
    	player = Game::instance.m_scene->get_game_object("Player1");
	    Vector2D pos = player->physics.position;
	    m_game_object->physics.velocity = pos - m_game_object->physics.position;
	    m_game_object->physics.velocity.normalize();
	    m_game_object->physics.velocity *= enemy->defaultVel;
	
    return true;
}