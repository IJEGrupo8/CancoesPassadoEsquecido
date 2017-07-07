#include "log.h"
#include "components/moveDirectionals.hpp"
#include "keyword.hpp"
#include "vector.hpp"
#include "game.hpp"
#include "tilemap.hpp"
#include "gamescene.hpp"

using namespace std;

bool MoveDirectionals::update(){

	bool keyFlag = false;

    if(Input::keyPressed(Input::UP))
    {
			auto map = (dynamic_cast<GameScene *>(Game::instance.m_scene))->get_active_room()->get_game_object("mapa");
        if((dynamic_cast<TileMap *>(map))->at(((m_game_object->physics.position.getX()+20)/32),((m_game_object->physics.position.getY()+32)/32),2)==1)
           keyFlag = false;
        else{
            keyFlag = true;
        }
        (dynamic_cast<Player *>(m_game_object))->moveUp();
    }
    if(Input::keyPressed(Input::DOWN))
    {
        cout << "AQUI???" << endl;

        auto map = (dynamic_cast<GameScene *>(Game::instance.m_scene))->get_active_room()->get_game_object("mapa");
        if((dynamic_cast<TileMap *>(map))->at(((m_game_object->physics.position.getX()+20)/32),((m_game_object->physics.position.getY()+42)/32),2)==1)
           keyFlag = false;
        else{
            keyFlag = true;
        }
        (dynamic_cast<Player *>(m_game_object))->moveDown();

        cout << "OU AQUI???" << endl;
    }
    if(Input::keyPressed(Input::RIGHT))
    {
				auto map = (dynamic_cast<GameScene *>(Game::instance.m_scene))->get_active_room()->get_game_object("mapa");
        if((dynamic_cast<TileMap *>(map))->at(((m_game_object->physics.position.getX()+20)/32),((m_game_object->physics.position.getY()+42)/32),2)==1)
           keyFlag = false;
        else{
            keyFlag = true;
        }
        (dynamic_cast<Player *>(m_game_object))->moveRight();
    }
    if(Input::keyPressed(Input::LEFT))
    {
				auto map = (dynamic_cast<GameScene *>(Game::instance.m_scene))->get_active_room()->get_game_object("mapa");
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
				(dynamic_cast<Player *>(m_game_object))->active_sprite->activeAnimation->clock.pauseTimer();
    }
	return true;
}
