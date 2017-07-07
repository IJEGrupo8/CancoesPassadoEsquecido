#include "imagescene.hpp"
#include "game.hpp"
#include "keyword.hpp"


using namespace engine;

bool ImageScene::update()
{
    if(Input::keyPressed(Input::ENTER))
    {
    	if(name() == "Menu" || name() == "Victory"){
    		engine::Game::instance.change_scene("stage_1");
    	}
    	else{
    		engine::Game::instance.change_scene("Menu");
        }
    }
    
    return true;
}
