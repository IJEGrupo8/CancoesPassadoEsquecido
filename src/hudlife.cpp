#include "gameobject.hpp"
#include "log.h"
#include "hudlife.hpp"

using namespace engine;

bool HUDLife::init()
{
    engine::GameObject::init();
    return true;
}

bool HUDLife::shutdown()
{
    engine::GameObject::shutdown();
    return true;
}

bool HUDLife::draw()
{
    double new_width = w * m_player->life / 100.0;
    m_life_content->setWidth(new_width);

    engine::GameObject::draw();

    return true;
}

bool HUDLife::update()
{
    engine::GameObject::update();
    return true;
}
