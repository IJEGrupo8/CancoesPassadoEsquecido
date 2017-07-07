#include "gameobject.hpp"
#include "components/image.hpp"
#include "components/audio.hpp"
#include "log.h"
#include "vector.hpp"
#include "spell.hpp"
#include "slamspell.hpp"
#include "timer.hpp"
#include "game.hpp"
#include "enemy.hpp"
#include "gamescene.hpp"

#define nframes 10

using namespace engine;

bool SlamSpell::init()
{
  Spell::init();

  return true;
}

bool SlamSpell::shutdown()
{
  Spell::shutdown();
  return true;
}

bool SlamSpell::draw()
{
  Spell::draw();

  return true;
}

bool SlamSpell::update()
{
  Spell::update();

  if(durationTimer.getTime()< duration){
    auto x = (dynamic_cast<GameScene *>(Game::instance.m_scene))->get_active_room()->m_objects;

    for (auto id_obj: x)
    {
        auto obj = id_obj.second;
        if ((dynamic_cast<Enemy*>(obj))) {

          physics.collisionBox.x = physics.position.getX();
          physics.collisionBox.y = physics.position.getY();
          physics.collisionBox.w = w;
          physics.collisionBox.h = h;

          obj->physics.collisionBox.x = obj->physics.position.getX();
          obj->physics.collisionBox.y = obj->physics.position.getY();
          obj->physics.collisionBox.w = obj->w;
          obj->physics.collisionBox.h = obj->h;

          if(physics.detectColision(obj))
          {
            obj->physics.velocity =(physics.velocity/2);
            (dynamic_cast<Enemy*>(obj))->canMove = false;

            //m_game_object->setState(GameObject::State::disabled);
          }else{
            //Bugado
            (dynamic_cast<Enemy*>(obj))->canMove = true;
          }
        }

    }

  }else{
   	//quita do scene
   	INFO("Finish spell");
    setState(State::disabled);

   	//Game::instance.m_scene->remove_game_object(name());
   }
   return true;
}

bool SlamSpell::useSpell()
{
  if(countdownTimer.getTime() > countdown){
    INFO("Start spell");

    setState(State::enabled);

    AudioComponent * audio = get_component<AudioComponent>();
    audio->play(1);

    physics.position = player->physics.position;
    physics.velocity = player->physics.velocity*3;

    durationTimer.startTimer();
    countdownTimer.startTimer();
    //timer2.startTimer();
    setup();
  }else{
    INFO("on countdown");
  }
  return true;
}
void SlamSpell::setup()
{
  Spell::setup();
}
