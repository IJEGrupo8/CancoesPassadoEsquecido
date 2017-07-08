#ifndef __GAME_PLAYER_OBJECT__
#define __GAME_PLAYER_OBJECT__

#include <string>
#include <list>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include "vector.hpp"
#include "gameobject.hpp"
#include "components/image.hpp"
#include "instrument.hpp"
#include "components/text.hpp"
#include "components/animationcontroller.hpp"

using namespace engine;

class Player : public GameObject {
public:
    Player() : GameObject() {}
    Player(std::string _name,int _x,int _y)
        : GameObject(_name,_x,_y) {}

    ~Player() {}
    
    int life = 100;
    int defaultVel = 10;


    virtual bool init();
    virtual bool shutdown();
    virtual bool update();
    virtual bool draw();

    bool moveDown();
    bool moveUp();
    bool moveRight();
    bool moveLeft();
    bool changeInstrument(std::string instrument);
    bool changeSprite(std::string sprite);
    bool handlePlayer();
    void addInstrument(std::string instrument_name, Instrument instrument);
    void addSprite(std::string instrument_name, AnimationControllerComponent * sprite);
    Instrument getActiveInstrument();
    void addFragment(int _id);
    TextComponent* nFragments;
    void clearFragments();
    AnimationControllerComponent * active_sprite;


private:
    std::unordered_map<std::string, Instrument> instruments;
    std::unordered_map<std::string, AnimationControllerComponent *> sprites;
    Instrument active_instrument;
    std::vector<int> fragments;
};

#endif
