#ifndef __MENU_SCENE__
#define __MENU_SCENE__

#include <string>
#include "scene.hpp"
#include "log.h"
#include "timer.hpp"

using namespace engine;

class MenuScene : public Scene{
public:

    MenuScene() : Scene("") {}
    MenuScene(std::string _name)
        : Scene(_name) {}

    ~MenuScene() {}
    bool update();
    bool selectButton();
    bool confirmButton();
    bool setSelectionIndicator();
    virtual bool init();
private:

    int selected[3];
    Timer timer;

/*
    virtual bool init();
    virtual bool shutdown();
    virtual bool draw();
    virtual 
    virtual bool verifyColision(GameObject* ob);
*/


};

#endif
