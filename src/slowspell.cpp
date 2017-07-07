#include "gameobject.hpp"
#include "components/image.hpp"
#include "components/audio.hpp"
#include "log.h"
#include "vector.hpp"
#include "spell.hpp"
#include "slowspell.hpp"
#include "timer.hpp"
#include "game.hpp"
#include "enemy.hpp"
#include "gamescene.hpp"
#include "gameglobals.hpp"

#define nframes 10

using namespace engine;

bool SlowSpell::init()
{
  Spell::init();

  return true;
}

bool SlowSpell::shutdown()
{
  Spell::shutdown();
  return true;
}

bool SlowSpell::draw()
{
  Spell::draw();

  return true;
}

bool SlowSpell::update()
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
          if(enemy_obj->getEnemyType() == globals::MAD_ENEMY){
            if(timer.getTime() < 3000) {
                enemy_obj->defaultVel = 1;                      
            }
            else {
              collided = false;
              enemy_obj->defaultVel = 3;
            }
          }
          else if(enemy_obj->getEnemyType() == globals::SAD_ENEMY){
            Player *playerObject = (dynamic_cast<Player*>(player));
            if(timer.getTime() < 3000) {
                playerObject->defaultVel = 1;                      
            }
            else {
              collided = false;
              playerObject->defaultVel = 5;
            }
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

bool SlowSpell::useSpell()
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
void SlowSpell::setup()
{
  Spell::setup();
}
