#include "gameobject.hpp"
#include "components/image.hpp"
#include "log.h"
#include "vector.hpp"
#include "spell.hpp"
#include "timer.hpp"
#include "game.hpp"

#define nframes 3

using namespace engine;

bool Spell::init()
{
    engine::GameObject::init();
     
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
  w = 100; h = 100;
  physics.position.setX(100);
  physics.position.setY(100);

  if(timer.getTime()<3000){
    
    INFO("xF = " << xF << " - w = " << w);

    int xFrame = (((xF/w)+1)%nframes)*w;
    int yFrame = 3*h; 

    xF = xFrame;
    yF = yFrame;

  }else{
   	//quita do scene
   	INFO("Finish spell");

   	Game::instance.m_scene->remove_game_object(name());
   }
   return true;
}

bool Spell::useSpell(){
	Game::instance.m_scene->add_game_object(*this);
  m_state = State::enabled;
	//adicionar na cena
	INFO("Start spell");
	timer.startTimer();
  return true;
}
