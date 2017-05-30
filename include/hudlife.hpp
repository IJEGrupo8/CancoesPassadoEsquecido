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
    HUDLife(std::string _name,int _x,int _y, Player *player)
        : GameObject(_name,_x,_y), m_player(player) {}

    ~HUDLife() {}
   
    virtual bool init();
    virtual bool shutdown();
    virtual bool update();
    virtual bool draw();
    void setLifeBar(ImageComponent *life_bar);
    void setLifeBarContent(CustomImageComponent *life_content);

private:
    ImageComponent *m_life_bar;
    CustomImageComponent *m_life_content;
    Player *m_player;
};

#endif
