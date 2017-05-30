#ifndef __GAME_HUDLIFE_OBJECT__
#define __GAME_HUDLIFE_OBJECT__

#include <string>
#include "gameobject.hpp"
#include "components/image.hpp"
#include "customimagecomponent.hpp"
#include "player.hpp"

using namespace engine;

class HUDLife : public GameObject {
public:
    HUDLife() : GameObject() {}
    HUDLife(std::string _name,int _x,int _y, Player *player, ImageComponent *life_bar, CustomImageComponent *life_content)
        : GameObject(_name,_x,_y), m_life_bar(life_bar), m_life_content(life_content), m_player(player) {}

    ~HUDLife() {}
   
    virtual bool init();
    virtual bool shutdown();
    virtual bool update();
    virtual bool draw();

private:
    ImageComponent *m_life_bar;
    CustomImageComponent *m_life_content;
    Player *m_player;
};

#endif
