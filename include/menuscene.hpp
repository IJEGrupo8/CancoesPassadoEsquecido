#ifndef __MENU_SCENE__
#define __MENU_SCENE__

#include <string>
#include "scene.hpp"
#include "log.h"

using namespace engine;

class MenuScene : public Scene{
public:

    MenuScene() : Scene("") {}
    MenuScene(std::string _name)
        : Scene(_name) {}

    ~MenuScene() {}
    bool update();
    bool isInsideButton(int buttonX, int buttonY, int clickX, int clickY, int buttonW, int buttonH);
    bool handleEvents();
private:

/*
    virtual bool init();
    virtual bool shutdown();
    virtual bool draw();
    virtual 
    virtual bool verifyColision(GameObject* ob);
*/


};

#endif
