#include "gameobject.hpp"
#include "log.h"
#include "hudbox.hpp"

using namespace engine;

bool HUDBox::init()
{
    engine::GameObject::init();
    return true;
}

bool HUDBox::shutdown()
{
    engine::GameObject::shutdown();
    return true;
}

bool HUDBox::draw()
{
    engine::GameObject::draw();

    return true;
}

bool HUDBox::update()
{
    engine::GameObject::update();
    return true;
}
