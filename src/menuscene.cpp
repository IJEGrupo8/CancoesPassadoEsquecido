#include "scene.hpp"
#include "menuscene.hpp"
#include "game.hpp"
#include "keyword.hpp"


using namespace engine;

bool MenuScene::update()
{
	handleEvents();

    if(Input::keyPressed(Input::ENTER))
    {
       engine::Game::instance.change_scene("stage_1_room_1");
    }
    
    return true;
}

bool MenuScene::handleEvents(){
	SDL_Event e;
    while(SDL_PollEvent(&e)){
    	INFO("ESTA NO HANDLE EVENTS " << e.type);
        switch(e.type){
            case SDL_MOUSEBUTTONDOWN:
            	INFO("CLICOU");
                if(e.button.button == SDL_BUTTON_LEFT){
                	int x = e.button.x;
                	int y = e.button.y;
                	INFO("CLICOU EM " << x << "E " << y);

                	GameObject * playButton = get_game_object("playbutton");
                	GameObject * optionsButton = get_game_object("optionsbutton");
                	GameObject * quitButton = get_game_object("quitbutton");

                	if(isInsideButton(playButton->physics.position.getX(),
                					  playButton->physics.position.getY(),
                					  x, y,
                					  playButton->w,
                					  playButton->h)){
                		INFO("CLICOU NO PLAY");
                	}
                	else if(isInsideButton(optionsButton->physics.position.getX(),
                					  optionsButton->physics.position.getY(),
                					  x, y,
                					  optionsButton->w,
                					  optionsButton->h)){
                		INFO("CLICOU NO OPTIONS");

                	}
                	else if(isInsideButton(quitButton->physics.position.getX(),
                					  quitButton->physics.position.getY(),
                					  x, y,
                					  quitButton->w,
                					  quitButton->h)){
                		INFO("CLICOU NO QUIT");
                	}                	
                }

                break;
        }
    }

    return true;
}

bool MenuScene::isInsideButton(int buttonX, int buttonY, int clickX, int clickY, 
	int buttonW, int buttonH){
	bool inside = true; 
 
	if ( clickX < buttonX ) { 
		inside = false; 
	} 
	else if( clickX > buttonX + buttonW ) { 
		inside = false; 
	} 
	else if( clickY < buttonY ) { 
		inside = false; 
	}
	else if( clickY > buttonY + buttonH ) { 
		inside = false; 
	}

	return inside;
}