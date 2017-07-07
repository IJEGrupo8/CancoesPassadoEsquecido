#include "gameobject.hpp"
#include "log.h"
#include "hudinstrument.hpp"
#include "gameglobals.hpp"
#include <string>
#include <sstream>
#include <iostream>
using namespace engine;

bool HUDInstrument::init()
{
    huds[globals::spellQ]->setState(Component::State::enabled);
    huds[globals::spellQ]->yOffset = -100;
    huds[globals::spellW]->setState(Component::State::enabled);
    huds[globals::spellW]->yOffset = -80;
    huds[globals::spellE]->setState(Component::State::enabled);
    huds[globals::spellE]->yOffset = -60;
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
    Spell * spellQ = m_player->getActiveInstrument().getSpell(globals::spellQ);
    std::stringstream ss;
    std::string available;
    if(spellQ->countdownTimer.getTime() > spellQ->countdown)
    {
        available = "PRONTO";
    }
    else 
    {
        available = "EM COOLDOWN";
    }
    ss << "Q:" << available;
    huds[globals::spellQ]->setText(ss.str());
    huds[globals::spellQ]->init();

    Spell * spellW = m_player->getActiveInstrument().getSpell(globals::spellW);
    std::stringstream ssW;
    std::string availableW;
    if(spellW->countdownTimer.getTime() > spellW->countdown)
    {
        availableW = "PRONTO";
    }
    else 
    {
        availableW = "EM COOLDOWN";
    }
    ssW << "W:" << availableW;
    huds[globals::spellW]->setText(ssW.str());
    huds[globals::spellW]->init();

    Spell * spellE = m_player->getActiveInstrument().getSpell(globals::spellE);
    std::stringstream ssE;
    std::string availableE;
    if(spellE->countdownTimer.getTime() > spellE->countdown)
    {
        availableE = "PRONTO";
    }
    else 
    {
        availableE = "EM COOLDOWN";
    }
    ssE << "E:" << availableE;
    huds[globals::spellE]->setText(ssE.str());
    huds[globals::spellE]->init();

    engine::GameObject::draw();

    return true;
}

bool HUDInstrument::update()
{
    engine::GameObject::update();
    return true;
}

void HUDInstrument::addHUD(std::string instrument_name, TextComponent* hud){
    huds[instrument_name] = hud;
}
