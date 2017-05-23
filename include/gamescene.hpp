#ifndef __GAME_SCENE__
#define __GAME_SCENE__

#include <string>
#include <unordered_map>

#include "scene.hpp"

using namespace engine;

class GameScene : public Scene{
public:

    GameScene() : Scene("") {}
    GameScene(std::string _name)
        : Scene(_name) {}

    ~GameScene() {}
    bool draw();
    bool update();
    bool init();
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
