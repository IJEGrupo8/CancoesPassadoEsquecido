#ifndef __GAME_HUDINSTRUMENT_OBJECT__
#define __GAME_HUDINSTRUMENT_OBJECT__

#include <string>
#include "gameobject.hpp"
#include "components/image.hpp"
#include "player.hpp"

using namespace engine;

class HUDInstrument : public GameObject {
public:
    HUDInstrument() : GameObject() {}
    HUDInstrument(std::string _name,int _x,int _y, Player *player)
        : GameObject(_name,_x,_y), m_player(player) {}

    ~HUDInstrument() {}
   
    virtual bool init();
    virtual bool shutdown();
    virtual bool update();
    virtual bool draw();
    void addHUD(std::string instrument_name, TextComponent* hud);

private:
    std::unordered_map<std::string, TextComponent*> huds;
    Player *m_player;
};

#endif
