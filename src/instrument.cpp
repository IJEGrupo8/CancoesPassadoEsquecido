#include "gameobject.hpp"
#include "components/image.hpp"
#include "log.h"
#include "vector.hpp"
#include "instrument.hpp"

using namespace engine;

bool Instrument::init()
{
    engine::GameObject::init();
 
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
   
}
