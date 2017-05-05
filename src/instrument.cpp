#include "gameobject.hpp"
#include "components/image.hpp"
#include "log.h"
#include "vector.hpp"
#include "instrument.hpp"
#include "gameglobals.hpp"


using namespace engine;

bool Instrument::init()
{
    engine::GameObject::init();
    for(auto spell : spells){
    	spell.second.init();
    }
 
    return true;
}

bool Instrument::shutdown()
{
    engine::GameObject::shutdown();
    return true;
}

bool Instrument::draw()
{
    engine::GameObject::draw();

    return true;
}

bool Instrument::update()
{
   return true;
}
bool Instrument::addSpell(std::string spell_name, Spell spell)
{
	spells[spell_name] = spell;
	return true;
}
bool Instrument::useSpellQ(){
	spells[globals::spellQ].useSpell();
	INFO("Using spell Q from " << name());
	return true;
}
bool Instrument::useSpellW(){
	spells[globals::spellW].useSpell();
	INFO("Using spell W from " << name());
	return true;
}
bool Instrument::useSpellE(){
	spells[globals::spellE].useSpell();
	INFO("Using spell E from " << name());
	return true;
}