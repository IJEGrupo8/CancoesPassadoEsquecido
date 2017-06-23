#include "scene.hpp"
#include "menuscene.hpp"
#include "game.hpp"
#include "keyword.hpp"
#include "components/image.hpp"
#include "timer.hpp"

using namespace engine;

bool MenuScene::init(){
	//set button 0 (play) as selected
	selected[0] = 1;
	selected[1] = 0;
	selected[2] = 0;
	timer.startTimer();
	engine::Scene::init();

	return true;
}

bool MenuScene::update()
{
	selectButton();
	setSelectionIndicator();
	confirmButton();
    
    return true;
}

bool MenuScene::selectButton()
{
	if(timer.getTime() > 200){
		if(Input::keyPressed(Input::DOWN)){
			timer.startTimer();
			if(selected[0]){
				INFO("ESTAVA NO PLAY APERTOU PRA BAIXO");
				selected[0] = 0;
				selected[1] = 1;
				selected[2] = 0;
			}
			else if(selected[1]){
				INFO("ESTAVA NO OPTIONS APERTOU PRA BAIXO");
				selected[0] = 0;
				selected[1] = 0;
				selected[2] = 1;
			}
			else if(selected[2]){
				INFO("ESTAVA NO QUIT APERTOU PRA BAIXO");
				selected[0] = 1;
				selected[1] = 0;
				selected[2] = 0;
			}
		}
		else if(Input::keyPressed(Input::UP)){
			timer.startTimer();
			if(selected[0]){
				INFO("ESTAVA NO PLAY APERTOU PRA CIMA");
				selected[0] = 0;
				selected[1] = 0;
				selected[2] = 1;
			}
			else if(selected[1]){
				INFO("ESTAVA NO OPTIONS APERTOU PRA CIMA");
				selected[0] = 1;
				selected[1] = 0;
				selected[2] = 0;
			}
			else if(selected[2]){
				INFO("ESTAVA NO QUIT APERTOU PRA CIMA");
				selected[0] = 0;
				selected[1] = 1;
				selected[2] = 0;
			}
		}
	}

	return true;
}

bool MenuScene::confirmButton(){
	if(Input::keyPressed(Input::ENTER))
    {
       if(selected[0]){
       	engine::Game::instance.change_scene("stage_1_room_1");
       }
       else if(selected[1]){
       	
       }
       else if(selected[2])
       {
       	engine::Game::instance.set_state(Game::State::exit_loop);
       }
    }

    return true;
}

bool MenuScene::setSelectionIndicator(){

	GameObject * playButton = get_game_object("playbutton");
	GameObject * optionsButton = get_game_object("optionsbutton");
	GameObject * quitButton = get_game_object("quitbutton");

	auto playButtonImage = playButton->get_component<ImageComponent>();
	auto optionsButtonImage = optionsButton->get_component<ImageComponent>();
	auto quitButtonImage = quitButton->get_component<ImageComponent>();

	if(selected[0]){
		SDL_SetTextureAlphaMod(playButtonImage->m_texture, 120.0);
		SDL_SetTextureAlphaMod(optionsButtonImage->m_texture, 255.0);
		SDL_SetTextureAlphaMod(quitButtonImage->m_texture, 255.0);
	}
	else if(selected[1]){
		SDL_SetTextureAlphaMod(playButtonImage->m_texture, 255.0);
		SDL_SetTextureAlphaMod(optionsButtonImage->m_texture, 120.0);
		SDL_SetTextureAlphaMod(quitButtonImage->m_texture, 255.0);
	}
	else if(selected[2]){
		SDL_SetTextureAlphaMod(playButtonImage->m_texture, 255.0);
		SDL_SetTextureAlphaMod(optionsButtonImage->m_texture, 255.0);
		SDL_SetTextureAlphaMod(quitButtonImage->m_texture, 120.0);
	}

    return true;
}