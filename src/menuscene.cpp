#include "scene.hpp"
#include "menuscene.hpp"
#include "game.hpp"
#include "log.h"
#include <string>
#include "keyword.hpp"


using namespace engine;

bool MenuScene::update()
{
    //auto playButton = m_objects["playbutton"];

    //const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
    if(Input::keyPressed(Input::X))
    {
       engine::Game::instance.change_scene("Gameplay");
    }
    
    return true;
}
