#ifndef __GAME_INSTRUMENT_OBJECT__
#define __GAME_INSTRUMENT_OBJECT__

#include <string>
#include <list>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include "vector.hpp"
#include "gameobject.hpp"
#include "spell.hpp"

using namespace engine;

class Instrument : public GameObject {
public:
    Instrument() : GameObject() {}
    Instrument(std::string _name,int _x,int _y)
        : GameObject(_name,_x,_y) {}

    ~Instrument() {}

    virtual bool init();
    virtual bool shutdown();
    virtual bool update();
    virtual bool draw();
    bool addSpell(std::string name, Spell spell);
    bool useSpellQ();
    bool useSpellW();
    bool useSpellE();

private:
    std::unordered_map<std::string, Spell> spells;
};

#endif