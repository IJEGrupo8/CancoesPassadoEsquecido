#ifndef __SLOW_SPELL__
#define __SLOW_SPELL__

#include <string>
#include <list>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include "vector.hpp"
#include "gameobject.hpp"
#include "timer.hpp"
#include "spell.hpp"

using namespace engine;

class StopSpell : public Spell {
public:
    StopSpell() : Spell() {}
    StopSpell(std::string _name, GameObject * obj, int _x, int _y,int _countdown,int _duration)
        : Spell(_name,obj,_x,_y,_countdown,_duration) {}

    ~StopSpell() {}

    
    bool init();
    bool shutdown();
    bool update();
    bool draw();
    void setup();
    bool useSpell();
private:
    Timer timer;
    bool collided;
};

#endif