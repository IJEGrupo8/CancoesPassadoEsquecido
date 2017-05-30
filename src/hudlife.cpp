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
    INFO("OIIIIIIIIIIIIIIII");
    double new_width = ((w-110) * m_player->life) / 100.0;
    double new_heith = h*0.5;
    m_life_content->setWidth(new_width);
    m_life_content->setHeight(new_heith);
    m_life_content->setX(physics.position.getX()+55);
    m_life_content->setY(physics.position.getY()+10);
    engine::GameObject::draw();

    return true;
}

bool HUDLife::update()
{
    engine::GameObject::update();
    return true;
}

void HUDLife::setLifeBar(ImageComponent *life_bar){
    m_life_bar = life_bar;
}

void HUDLife::setLifeBarContent(CustomImageComponent *life_content){
    m_life_content = life_content;
}