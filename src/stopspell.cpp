#include "gameobject.hpp"
#include "components/image.hpp"
#include "components/audio.hpp"
#include "log.h"
#include "vector.hpp"
#include "spell.hpp"
#include "stopspell.hpp"
#include "timer.hpp"
#include "game.hpp"
#include "enemy.hpp"
#include "gamescene.hpp"

#define nframes 10

using namespace engine;

bool StopSpell::init()
{
  Spell::init();

  return true;
}

bool StopSpell::shutdown()
{
  Spell::shutdown();
  return true;
}

bool StopSpell::draw()
{
  Spell::draw();

  return true;
}

bool StopSpell::update()
{
  Spell::update();

  auto time = durationTimer.getTime();
  if(time <= duration){
    auto x = (dynamic_cast<GameScene *>(Game::instance.m_scene))->get_active_room()->m_objects;

    for (auto id_obj: x)
    {
      auto obj = id_obj.second;
      auto enemy_obj = (dynamic_cast<Enemy*>(obj));
      if (enemy_obj) {

        physics.collisionBox.x = physics.position.getX();
        physics.collisionBox.y = physics.position.getY();
        physics.collisionBox.w = w;
        physics.collisionBox.h = h;

        enemy_obj->physics.collisionBox.x = enemy_obj->physics.position.getX();
        enemy_obj->physics.collisionBox.y = enemy_obj->physics.position.getY();
        enemy_obj->physics.collisionBox.w = enemy_obj->w;
        enemy_obj->physics.collisionBox.h = enemy_obj->h;

        if(physics.detectColision(enemy_obj))
        {
          collided = true;
        }

        if(collided){
          if(timer.getTime() < 5000) {
            enemy_obj->canMove = false;
          }
          else {
            collided = false;
            enemy_obj->canMove = true;
          }
        }
      }
    }
  }else{
 
   	INFO("Finish spell");
    setState(State::disabled);
   }
   return true;
}

bool StopSpell::useSpell()
{
  if(countdownTimer.getTime() > countdown){
    INFO("Start spell");

    setState(State::enabled);

    AudioComponent * audio = get_component<AudioComponent>();
    audio->play(1);

    physics.position = player->physics.position;
    physics.velocity = player->physics.velocity*3;

    durationTimer.startTimer();
    timer.startTimer();
    countdownTimer.startTimer();

    setup();
  }else{
    INFO("on countdown");
  }
  return true;
}
void StopSpell::setup()
{
  Spell::setup();
}
