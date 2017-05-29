#ifndef __GAMEOVER_SCENE__
#define __GAMEOVER_SCENE__

#include <string>
#include "scene.hpp"

using namespace engine;

class GameOverScene : public Scene{
public:

    GameOverScene() : Scene("") {}
    GameOverScene(std::string _name)
        : Scene(_name) {}

    ~GameOverScene() {}
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
