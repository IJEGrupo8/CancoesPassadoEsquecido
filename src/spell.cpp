#include "gameobject.hpp"
#include "components/image.hpp"
#include "components/audio.hpp"
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

  

  return true;
}

bool Spell::useSpell()
{
  //Implemente nos filhos
  INFO("Use Spell on spell");
  return true;
}
void Spell::setup()
{
  xF = 0;
  yF = 0;
  GameObject::setup();
}
