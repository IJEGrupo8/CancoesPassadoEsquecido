#ifndef __GAME_HUDBOX_OBJECT__
#define __GAME_HUDBOX_OBJECT__

#include <string>
#include "gameobject.hpp"
#include "components/image.hpp"
#include "customimagecomponent.hpp"
#include "player.hpp"

using namespace engine;

class HUDBox : public GameObject {
public:
    HUDBox() : GameObject() {}
    HUDBox(std::string _name,int _x,int _y)
        : GameObject(_name,_x,_y) {}

    ~HUDBox() {}
   
    virtual bool init();
    virtual bool shutdown();
    virtual bool update();
    virtual bool draw();
    
};

#endif
