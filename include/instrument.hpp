#ifndef __GAME_INSTRUMENT_OBJECT__
#define __GAME_INSTRUMENT_OBJECT__

#include <string>
#include <list>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include "vector.hpp"
#include "gameobject.hpp"

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

private:
    
};

#endif