#include "room.hpp"
#include "scene.hpp"
#include "log.h"

using namespace engine;

bool Room::init(){
    return Scene::init();
}

bool Room::update()
{
    return Scene::update();
}

bool Room::draw()
{
    return Scene::draw();;
}
