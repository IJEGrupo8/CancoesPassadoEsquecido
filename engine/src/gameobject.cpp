#include "gameobject.hpp"

#include "components/text.hpp"
#include "components/image.hpp"
#include "components/animation.hpp"
#include "components/code.hpp"
#include "components/animationcontroller.hpp"

#include "log.h"

using namespace engine;

bool GameObject::init()
{
    INFO("Init game object " << m_name);

    for(auto id_componentlist: m_components)
    {
        for (auto component: id_componentlist.second)
        {
            if(component->state() == Component::State::enabled &&
               component->init() == false) return false;
        }
    }

    return true;
}

bool GameObject::shutdown()
{
    INFO("Shutdown game object " << m_name);

    for(auto id_componentlist: m_components)
    {
        for (auto component: id_componentlist.second)
        {
            if(component->state() == Component::State::enabled &&
               component->shutdown() == false) return false;
        }
    }

    return true;
}

bool GameObject::draw()
{
    for(auto component: m_components[std::type_index(typeid(ImageComponent))])
    {
        if(component->state() == Component::State::enabled){
            (dynamic_cast<ImageComponent *>(component))->draw();
        }
    }

    for(auto component: m_components[std::type_index(typeid(TextComponent))])
    {
        if(component->state() == Component::State::enabled)
            (dynamic_cast<TextComponent *>(component))->draw();
    }

    for(auto component: m_components[std::type_index(typeid(AnimationControllerComponent))])
    {
        if(component->state() == Component::State::enabled)
            (dynamic_cast<AnimationControllerComponent *>(component))->draw();
    }
    for(auto component: m_components[std::type_index(typeid(AnimationComponent))])
    {
        if(component->state() == Component::State::enabled)
            (dynamic_cast<AnimationComponent *>(component))->draw();
    }
    return true;
}
void GameObject::setup()
{
    for(auto component: m_components[std::type_index(typeid(AnimationControllerComponent))])
    {
        if(component->state() == Component::State::enabled)
            (dynamic_cast<AnimationControllerComponent *>(component))->setup();
    }
    for(auto component: m_components[std::type_index(typeid(AnimationComponent))])
    {
        if(component->state() == Component::State::enabled)
            (dynamic_cast<AnimationComponent *>(component))->setup();
    }

}
bool GameObject::add_component(Component & component)
{
    INFO("Adding component to game object " << m_name);
    m_components[std::type_index(typeid(component))].push_back(&component);

    INFO("Game object " << m_name << " added");

    return true;
}

bool GameObject::update()
{
    INFO("teste gameobject before");
    physics.velocity += physics.aceleration;
    physics.position += physics.velocity;

    for(auto componentList: m_components)//fazer para todos os components
    {
        for(auto component : componentList.second)
        {
            INFO("teste component before");
            if(component->state() == Component::State::enabled)
                component->update();
            INFO("teste component after");
        }
    }
    INFO("teste gameobject after");

    return true;
}

