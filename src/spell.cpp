#include "gameobject.hpp"
#include "components/image.hpp"
#include "log.h"
#include "vector.hpp"
#include "spell.hpp"
#include "timer.hpp"
#include "game.hpp"


#define nframes 4

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

  if(timer.getTime()<3000){
    
    INFO("xF = " << xF << " - w = " << w);

    int xFrame = (((xF/w)+1)%nframes)*w;
    int yFrame = 1*h; 

    xF = xFrame;
    yF = yFrame;

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

  return true;
}
