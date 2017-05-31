#include "log.h"
#include "components/pushenemy.hpp"
#include "vector.hpp"
#include "game.hpp"
#include "enemy.hpp"
#include "gameobject.hpp"


bool PushEnemy::init(){
    return true;
}

bool PushEnemy::update(){

    auto x = Game::instance.m_scene->m_objects;
    for (auto id_obj: x)
    {
        auto obj = id_obj.second;
        if ((dynamic_cast<Enemy*>(obj))) {
        	
        	m_game_object->physics.collisionBox.x = m_game_object->physics.position.getX();
		    m_game_object->physics.collisionBox.y = m_game_object->physics.position.getY();
		    m_game_object->physics.collisionBox.w = m_game_object->w;
		    m_game_object->physics.collisionBox.h = m_game_object->h;

		    obj->physics.collisionBox.x = obj->physics.position.getX();
		    obj->physics.collisionBox.y = obj->physics.position.getY();
		    obj->physics.collisionBox.w = obj->w;
		    obj->physics.collisionBox.h = obj->h;
        	if(m_game_object->physics.detectColision(obj))
		    {
		        obj->physics.velocity +=(m_game_object->physics.velocity);
		        //m_game_object->setState(GameObject::State::disabled);
		    }
        }
        	
        
    }
    return true;
}