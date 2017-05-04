#ifndef __MENU_SCENE__
#define __MENU_SCENE__

#include <string>
#include <unordered_map>

#include "scene.hpp"

using namespace engine;

class MenuScene : public Scene{
public:

    MenuScene() : Scene("") {}
    MenuScene(std::string _name)
        : Scene(_name) {}

    ~MenuScene() {}
    bool update();
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
