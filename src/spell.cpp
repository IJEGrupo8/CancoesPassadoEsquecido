#include "gameobject.hpp"
#include "components/image.hpp"
#include "log.h"
#include "vector.hpp"
#include "spell.hpp"
#include "timer.hpp"
#include "game.hpp"

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
   if(timer.getTime()<3000){
   	//do some
   	INFO("Executing spell");

   }else{
   	//quita do scene
   	INFO("Finish spell");

   	Game::instance.m_scene->remove_game_object(name());


   }
}
bool Spell::useSpell(){
	Game::instance.m_scene->add_game_object(*this);
	//adicionar na cena
	INFO("Start spell");
	timer.startTimer();
}
