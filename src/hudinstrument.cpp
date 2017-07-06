#include "gameobject.hpp"
#include "log.h"
#include "hudinstrument.hpp"
#include "gameglobals.hpp"

using namespace engine;

bool HUDInstrument::init()
{
    engine::GameObject::init();
    return true;
}

bool HUDInstrument::shutdown()
{
    engine::GameObject::shutdown();
    return true;
}

bool HUDInstrument::draw()
{
    if(m_player->getActiveInstrument().name() == globals::banjo){
        active_hud = huds[globals::banjo];
        huds[globals::eletric_guitar]->setState(Component::State::disabled);
        huds[globals::accordion]->setState(Component::State::disabled);
    }
    else if(m_player->getActiveInstrument().name() == globals::eletric_guitar){
        active_hud = huds[globals::eletric_guitar];
        huds[globals::banjo]->setState(Component::State::disabled);
        huds[globals::accordion]->setState(Component::State::disabled);
    }
    else if(m_player->getActiveInstrument().name() == globals::accordion){
        active_hud = huds[globals::accordion];
        huds[globals::eletric_guitar]->setState(Component::State::disabled);
        huds[globals::banjo]->setState(Component::State::disabled);
    }

    active_hud->setState(Component::State::enabled);

    engine::GameObject::draw();

    return true;
}

bool HUDInstrument::update()
{
    engine::GameObject::update();
    return true;
}

void HUDInstrument::addHUD(std::string instrument_name, ImageComponent* hud){
    huds[instrument_name] = hud;
}
