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
    Spell(std::string _name, GameObject * obj, int _x, int _y)
        : GameObject(_name,_x,_y), player(obj) {}

    ~Spell() {}

    GameObject * player;
    Timer timer;
    Timer timer2;
    int linha = 0;
    int coluna = 0;
    int m_current_frame = 0;
    virtual bool init();
    virtual bool shutdown();
    virtual bool update();
    virtual bool draw();
    bool useSpell();
private:
    
};

#endif