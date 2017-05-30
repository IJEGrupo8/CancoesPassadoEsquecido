#include "log.h"
#include "components/chest.hpp"
#include "vector.hpp"
#include "game.hpp"




bool ChestComponent::init(){
    return true;
}
bool ChestComponent::update(){

    player = Game::instance.m_scene->get_game_object("Player1");
    Vector2D pos = player->physics.position;
    Vector2D diference = pos - m_game_object->physics.position;

    if(abs(diference.getX())<30 && abs(diference.getY())<30){
    	//adiciona no player
    	m_game_object->setState(GameObject::State::disabled);
    	INFO("SOME DIABO")
    }


    return true;
}