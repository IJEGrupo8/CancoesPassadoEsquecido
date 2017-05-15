#ifndef __GAME_SPELL_OBJECT__
#define __GAME_SPELL_OBJECT__

#include <string>
#include <list>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include "vector.hpp"
#include "gameobject.hpp"
#include "timer.hpp"

using namespace engine;

class Spell : public GameObject {
public:
    Spell() : GameObject() {}
    Spell(std::string _name, GameObject * obj, int _x, int _y,int _countdown,int _duration)
        : GameObject(_name,_x,_y), player(obj),countdown(_countdown),duration(_duration)  {}

    ~Spell() {}

    GameObject * player;
    Timer durationTimer;
    Timer countdownTimer;
    int countdown;
    int lastTimeUsed;
    int duration;
    
    bool init();
    bool shutdown();
    bool update();
    bool draw();
    void setup();
    bool useSpell();
private:
    
};

#endif