#include "scene.hpp"
#include "log.h"
#include <string>
#include "sdl2include.h"
using namespace engine;

GameObject INVALID_GAME_OBJECT;

bool Scene::add_game_object(GameObject & obj)
{
    auto id = obj.name();
    INFO("Add game object " << id << " to scene " << m_name);

    if (m_objects.find(id) != m_objects.end())
    {
        WARN("Game object " << id << " already exists!");
        return false;
    }

    m_objects[id] = &obj;
    return true;
}

GameObject & Scene::get_game_object(const std::string & id)
{
    if (m_objects.find(id) == m_objects.end())
    {
        WARN("Could not find game object " << id);
        return INVALID_GAME_OBJECT;
    }

    return *m_objects[id];
}

bool Scene::remove_game_object(const std::string & id)
{
    INFO("Remove game object " << id << " from scene " << m_name);

    if (m_objects.find(id) == m_objects.end())
    {
        WARN("Could not find game object " << id);
        return false;
    }

    m_objects.erase(id);
    return true;
}

bool Scene::init()
{
    INFO("Init scene " << m_name);

    for (auto id_obj: m_objects)
    {
        auto obj = id_obj.second;
        if (obj->state() == GameObject::State::enabled &&
            obj->init() == false) return false;
    }

    return true;
}

bool Scene::shutdown()
{
    INFO("Shutdown scene " << m_name);

    for (auto id_obj: m_objects)
    {
        auto obj = id_obj.second;
        if (obj->state() == GameObject::State::enabled &&
            obj->shutdown() == false) return false;
    }

    return true;
}

bool Scene::draw()
{
    for (auto id_obj: m_objects)
    {
        auto obj = id_obj.second;
        if (obj->state() == GameObject::State::enabled &&
            obj->draw() == false) return false;
    }

    return true;
}
bool Scene::update()
{
    for (auto id_obj: m_objects)
    {
        auto obj = id_obj.second;
        if (obj->state() == GameObject::State::enabled &&
            obj->update() == false) return false;
    }
    return true;
}
