#include "log.h"
#include "components/talknpc.hpp"
#include "keyword.hpp"
#include "player.hpp"
#include "game.hpp"

bool TalkNpc::init(){            
    line->setState(State::disabled);
    line->init();
    timer.startTimer();
    return true;
}
bool TalkNpc::update(){
    m_game_object->physics.collisionBox.x = m_game_object->physics.position.getX();
    m_game_object->physics.collisionBox.y = m_game_object->physics.position.getY();
    m_game_object->physics.collisionBox.w = m_game_object->w;
    m_game_object->physics.collisionBox.h = m_game_object->h;

    player = dynamic_cast<Player *>(Game::instance.m_scene->get_game_object("Player1"));

    if(timer.getTime() > 1000){

        if(m_game_object->physics.detectColision(player) && Input::keyPressed(Input::A)){
            line->setState(State::enabled);
            timer.startTimer();
        }else{
            line->setState(State::disabled);
        }
    }

    return true;
}