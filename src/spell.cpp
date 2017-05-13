#include "gameobject.hpp"
#include "components/image.hpp"
#include "log.h"
#include "vector.hpp"
#include "spell.hpp"
#include "timer.hpp"
#include "game.hpp"


#define nframes 10

using namespace engine;

bool Spell::init()
{
    engine::GameObject::init();
    setState(State::disabled);

    return true;
}

bool Spell::shutdown()
{
    engine::GameObject::shutdown();
    return true;
}

bool Spell::draw()
{
    engine::GameObject::draw();

    return true;
}

bool Spell::update()
{
  GameObject::update();

  if(timer.getTime()<1000){
    
    if(timer2.getTime() > 1000/16)
    {
      m_current_frame++;
      timer2.startTimer();
    }
      
    INFO("xF = " << xF << " - yF = " << yF);

    int col = (m_current_frame%4)*w;
    int lin = (m_current_frame/4)*h;

    xF = col;
    yF = lin;
  }else{
   	//quita do scene
   	INFO("Finish spell");
    setState(State::disabled);

   	//Game::instance.m_scene->remove_game_object(name());
   }
   return true;
}

bool Spell::useSpell(){
  INFO("Start spell");

  setState(State::enabled);
  physics.position = player->physics.position;
  physics.velocity = player->physics.velocity;
	timer.startTimer();
  timer2.startTimer();
  xF = 0;
  yF = 0;
  m_current_frame = 0;
  return true;
}
