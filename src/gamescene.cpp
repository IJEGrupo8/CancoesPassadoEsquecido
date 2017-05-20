#include "gamescene.hpp"
#include "scene.hpp"
#include "log.h"
#include <string>
#include "keyword.hpp"
#include "player.hpp"

using namespace engine;

bool GameScene::init(){
    Scene::init();
    return true;
}

bool GameScene::update()
{    
    Scene::update();

    return true;
}

bool GameScene::draw()
{
    Scene::draw();

    return true;
}