#include "gameobject.hpp"
#include "components/image.hpp"
#include "components/audio.hpp"
#include "log.h"
#include "vector.hpp"
#include "spell.hpp"
#include "basicspell.hpp"
#include "timer.hpp"
#include "game.hpp"
#include "enemy.hpp"
#include "gameglobals.hpp"
#include "gamescene.hpp"

#define nframes 10

using namespace engine;

bool BasicSpell::init()
{
  Spell::init();

  return true;
}

bool BasicSpell::shutdown()
{
  Spell::shutdown();
  return true;
}

bool BasicSpell::draw()
{
  Spell::draw();

  return true;
}

bool BasicSpell::update()
{
  Spell::update();

  if(durationTimer.getTime()< duration){
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
            if(enemy_obj->getEnemyType() == globals::SAD_ENEMY){ 
              enemy_obj->physics.velocity = (physics.velocity/2);
            }               
          }

          if(collided){
            if(enemy_obj->getEnemyType() == globals::MAD_ENEMY){
              if(timer.getTime() < 5000) {
                enemy_obj->defaultVel = 5;
              }
              else {
                collided = false;
                enemy_obj->defaultVel = 3;
              } 
            }
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

bool BasicSpell::useSpell()
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
    //timer2.startTimer();
    setup();
  }else{
    INFO("on countdown");
  }
  return true;
}
void BasicSpell::setup()
{
  Spell::setup();
}
