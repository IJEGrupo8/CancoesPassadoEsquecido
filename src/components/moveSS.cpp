#include "log.h"
#include "components/moveSS.hpp"
#include "keyword.hpp"
#include "vector.hpp"
#include "timer.hpp"

bool MoveSSDirectionals::init(){
    m_game_object->physics.velocity.setY(3);
    timer.startTimer();

    return true;
}
bool MoveSSDirectionals::update(){
	if(timer.getTime() < 1000){
        //m_game_object->physics.velocity*-1;
    }else{
        timer.startTimer();
        if(m_game_object->physics.velocity.getY() > 0) {
            m_game_object->physics.velocity.setY(-2);
            m_game_object->yF = 3*m_game_object->h;
            m_game_object->xF = (((m_game_object->xF/m_game_object->w)+1)%4)*m_game_object->w;

        }
        else if(m_game_object->physics.velocity.getY() < 0){
            m_game_object->physics.velocity.setY(2);
            m_game_object->yF = 0;
            m_game_object->xF = (((m_game_object->xF/m_game_object->w)+1)%4)*m_game_object->w;
        }
        INFO("Velocidade = " << m_game_object->physics.velocity.getY());

    }
	return true;
}