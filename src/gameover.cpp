#include "gameover.hpp"
#include "game.hpp"
#include "keyword.hpp"


using namespace engine;

bool GameOverScene::update()
{

    if(Input::keyPressed(Input::ENTER))
    {
       engine::Game::instance.change_scene("Menu");
    }
    
    return true;
}
