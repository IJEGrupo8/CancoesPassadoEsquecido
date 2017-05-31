#include "gameobject.hpp"
#include "player.hpp"
#include "components/text.hpp"
#include "components/image.hpp"
#include "log.h"
#include "vector.hpp"
#include "keyword.hpp"
#include "gameglobals.hpp"
#include <sstream>
#include "game.hpp"


#define nframes 4

using namespace engine;

bool Player::init()
{
    engine::GameObject::init();

    for(auto instrument : instruments){
        instrument.second.init();
    }

    active_instrument = instruments[globals::banjo];
    active_sprite = sprites[globals::banjo];

    sprites[globals::eletric_guitar]->setState(Component::State::disabled);
    sprites[globals::accordion]->setState(Component::State::disabled);

    life = 100;
    //INFO("x"<<physics.collisionBox.x<<"  y"<<physics.collisionBox.y <<"  w"<<physics.collisionBox.w<< "    h"<< physics.collisionBox.h)
    return true;
}

bool Player::shutdown()
{
    engine::GameObject::shutdown();
    return true;
}

bool Player::draw()
{
    engine::GameObject::draw();
    return true;
}

bool Player::update()
{
    handlePlayer();

    GameObject::update();
    
    int collisionAdjust = 0;
    physics.collisionBox.x = physics.position.getX() + collisionAdjust;
    physics.collisionBox.y = physics.position.getY() + collisionAdjust;
    physics.collisionBox.w = w - collisionAdjust;
    physics.collisionBox.h = h - collisionAdjust;

    return true;
}
bool Player::moveDown(){
    // Update Velocity
    int componentX = 0;
    int componentY = 10;

    Vector2D move(componentX,componentY);
    physics.velocity = move;
    // Update Frame
    int xFrame = (((xF/w)+1)%nframes)*w;
    int yFrame = 0*h;

    xF = xFrame;
    yF = yFrame;
    return true;
}

bool Player::moveUp(){
    // Update Velocity
    int componentX = 0;
    int componentY = -10;

    Vector2D move(componentX,componentY);
    physics.velocity = move;
    // Update Frame
    int xFrame = (((xF/w)+1)%nframes)*w;
    int yFrame = 3*h;

    xF = xFrame;
    yF = yFrame;
    return true;
}

bool Player::moveLeft(){
    // Update Velocity
    int componentX = -10;
    int componentY = 0;

    Vector2D move(componentX,componentY);
    physics.velocity = move;
    // Update Frame
    int xFrame = (((xF/w)+1)%nframes)*w;
    int yFrame = 1*h;

    xF = xFrame;
    yF = yFrame;
    return true;
}

bool Player::moveRight(){
    // Update Velocity
    int componentX = 10;
    int componentY = 0;

    Vector2D move(componentX,componentY);
    physics.velocity = move;
    // Update Frame
    int xFrame = (((xF/w)+1)%nframes)*w;
    int yFrame = 2*h;

    xF = xFrame;
    yF = yFrame;
    return true;
}

bool Player::changeInstrument(std::string instrument_name){
    INFO("Changing Instrument to " << instrument_name);
    Instrument instrument = instruments[instrument_name];
    bool isInstrumentNull = true;

    active_instrument = instrument;
    changeSprite(instrument_name);

    return isInstrumentNull;
}

bool Player::changeSprite(std::string sprite_name){
    INFO("Changing Sprite to " << sprite_name);
    ImageComponent* sprite = sprites[sprite_name];
   
    active_sprite->setState(Component::State::disabled);
    sprite->setState(Component::State::enabled);
    active_sprite = sprite;

    return true;
}

bool Player::handlePlayer(){
    
    if(Input::keyPressed(Input::ONE))
    {
        changeInstrument(globals::banjo);
    }
    if(Input::keyPressed(Input::TWO))
    {
        changeInstrument(globals::eletric_guitar);
    }
    if(Input::keyPressed(Input::THREE))
    {
        changeInstrument(globals::accordion);
    }
    if(Input::keyPressed(Input::Q))
    {
        active_instrument.useSpellQ();
    }
    if(Input::keyPressed(Input::W))
    {
        active_instrument.useSpellW();
    }
    if(Input::keyPressed(Input::E))
    {
        active_instrument.useSpellE();
    }


 
    /*if(keyFlag){
        
        if(collision) {
            player1->physics.velocity-=  player1->physics.collisionObj*3;
            INFO("Colidindo");
        }
        
    }*/
    
    return true;
}

void Player::addInstrument(std::string instrument_name, Instrument instrument){
    instruments[instrument_name] = instrument;
}

void Player::addSprite(std::string instrument_name, ImageComponent * sprite){
    sprites[instrument_name] = sprite;
}

Instrument Player::getActiveInstrument(){
    return active_instrument;
}

void Player::addFragment(int _id){
    fragments.push_back(_id);
    if(fragments.size() == 2) {
        engine::Game::instance.change_scene("Victory");
        physics.position.setX(getInitialX());
        physics.position.setY(getInitialY());
    }

    std::stringstream ss;
    ss << "Numero de fragmentos: "<<fragments.size();
    

    nFragments->setText(ss.str());
    nFragments->init();
}
