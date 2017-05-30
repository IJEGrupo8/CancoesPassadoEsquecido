#include "log.h"
#include "components/moveDirectionals.hpp"
#include "keyword.hpp"
#include "vector.hpp"
#include "game.hpp"
#include "tilemap.hpp"

bool MoveDirectionals::update(){

	bool keyFlag = false;

    if(Input::keyPressed(Input::UP))
    {
        auto map = Game::instance.m_scene->get_game_object("mapa");
        if((dynamic_cast<TileMap *>(map))->at((m_game_object->physics.position.getX()/32)-1,(m_game_object->physics.position.getY()/32)-2,2)==1)
           keyFlag = false;     
        else{
            keyFlag = true;
        }
        (dynamic_cast<Player *>(m_game_object))->moveUp();
    }
    if(Input::keyPressed(Input::DOWN))
    {
        (dynamic_cast<Player *>(m_game_object))->moveDown();
        keyFlag = true;
    }
    if(Input::keyPressed(Input::RIGHT))
    {
        (dynamic_cast<Player *>(m_game_object))->moveRight();
        keyFlag = true;
    }
    if(Input::keyPressed(Input::LEFT))
    {
        (dynamic_cast<Player *>(m_game_object))->moveLeft();
        keyFlag = true;
    }

    if(!keyFlag){
        Vector2D nulo(0,0);
        m_game_object->physics.velocity = nulo;
    }
	return true;
}