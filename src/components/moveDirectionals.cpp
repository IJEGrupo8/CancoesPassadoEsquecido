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
        if((dynamic_cast<TileMap *>(map))->at(((m_game_object->physics.position.getX()+20)/32),((m_game_object->physics.position.getY()+32)/32),2)==1)
           keyFlag = false;     
        else{
            keyFlag = true;
        }
        (dynamic_cast<Player *>(m_game_object))->moveUp();
    }
    if(Input::keyPressed(Input::DOWN))
    {

        auto map = Game::instance.m_scene->get_game_object("mapa");
        if((dynamic_cast<TileMap *>(map))->at(((m_game_object->physics.position.getX()+20)/32),((m_game_object->physics.position.getY()+42)/32),2)==1)
           keyFlag = false;     
        else{
            keyFlag = true;
        }
        (dynamic_cast<Player *>(m_game_object))->moveDown();
    }
    if(Input::keyPressed(Input::RIGHT))
    {
        auto map = Game::instance.m_scene->get_game_object("mapa");
        if((dynamic_cast<TileMap *>(map))->at(((m_game_object->physics.position.getX()+20)/32),((m_game_object->physics.position.getY()+42)/32),2)==1)
           keyFlag = false;     
        else{
            keyFlag = true;
        }
        (dynamic_cast<Player *>(m_game_object))->moveRight();
    }
    if(Input::keyPressed(Input::LEFT))
    {
        auto map = Game::instance.m_scene->get_game_object("mapa");
        if((dynamic_cast<TileMap *>(map))->at(((m_game_object->physics.position.getX())/32),((m_game_object->physics.position.getY()+42)/32),2)==1)
           keyFlag = false;     
        else{
            keyFlag = true;
        }
        (dynamic_cast<Player *>(m_game_object))->moveLeft();
    }

    if(!keyFlag){
        Vector2D nulo(0,0);
        m_game_object->physics.velocity = nulo;
    }
	return true;
}