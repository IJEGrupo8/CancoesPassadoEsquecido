#include "log.h"
#include "components/damageEnemy.hpp"
#include "vector.hpp"
#include "game.hpp"
#include "gamescene.hpp"
#include "gameglobals.hpp"
#include "player.hpp"

bool DamageEnemy::init(){

    INFO("Init changeroom");
    
    return true;
}
bool DamageEnemy::update(){
    m_game_object->physics.collisionBox.x = m_game_object->physics.position.getX();
    m_game_object->physics.collisionBox.y = m_game_object->physics.position.getY();
    m_game_object->physics.collisionBox.w = m_game_object->w;
    m_game_object->physics.collisionBox.h = m_game_object->h;
	
    player = dynamic_cast<Player *>(Game::instance.m_scene->get_game_object("Player1"));


    if(m_game_object->physics.detectColision(player))
    {
        player->life -= 10;
        player->physics.velocity = (m_game_object->physics.velocity * 5);
        
    }

    if(player->life <= 0)
    {
        engine::Game::instance.change_scene("Gameover");
        player->physics.position.setX(player->getInitialX());
        player->physics.position.setY(player->getInitialY());
        player->life = 100;

    }
    return true;
}