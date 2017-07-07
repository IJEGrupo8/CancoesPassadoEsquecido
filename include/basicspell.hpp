#ifndef __BASIC_SPELL__
#define __BASIC_SPELL__

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

class BasicSpell : public Spell {
public:
    BasicSpell() : Spell() {}
    BasicSpell(std::string _name, GameObject * obj, int _x, int _y,int _countdown,int _duration)
        : Spell(_name,obj,_x,_y,_countdown,_duration) {}

    ~BasicSpell() {}

    
    bool init();
    bool shutdown();
    bool update();
    bool draw();
    void setup();
    bool useSpell();
private:
    Timer timer;
    bool collided = false;
    
};

#endif