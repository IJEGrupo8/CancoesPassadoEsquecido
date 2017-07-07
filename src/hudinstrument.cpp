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
    huds["spellQ"]->setState(Component::State::enabled);
    huds["spellQ"]->xOffset = 10;
    huds["spellQ"]->yOffset = -200;
    huds["spellW"]->setState(Component::State::disabled);
    huds["spellE"]->setState(Component::State::disabled);
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
    huds["spellQ"]->setText(ss.str());
    huds["spellQ"]->init();



    // Spell * spellW = m_player->getActiveInstrument().getSpell("spellWBanjo");
    // Spell * spellE = m_player->getActiveInstrument().getSpell("spellEBanjo");
 
    // if(spellQ->countdownTimer.getTime() < spellQ->countdown)
    // {
    //     INFO("Q INATIVO");
    //     huds["spellQ"]->setState(Component::State::enabled);
    // }
    // else
    // {
    //     INFO("Q ATIVO");
    //     huds["spellQ"]->setState(Component::State::disabled);
    // }

    // if(spellW->countdownTimer.getTime() > countdown)
    // {
    //     huds["spellW"].setState(Component::State::enabled);
    // }
    // else
    // {
    //     huds["spellW"].setState(Component::State::disabled);
    // }

    // if(spellE->countdownTimer.getTime() > countdown)
    // {
    //     huds["spellE"].setState(Component::State::enabled);
    // }
    // else
    // {       
    //     huds["spellE"].setState(Component::State::disabled);
    // }

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
