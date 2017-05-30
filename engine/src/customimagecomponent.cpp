#include "components/image.hpp"
#include "customimagecomponent.hpp"
#include "log.h"

using namespace engine;

bool CustomImageComponent::init(){
	ImageComponent::init();
	return true;
}

void CustomImageComponent::draw(){

	    SDL_Rect renderQuad = {
        m_x,
        m_y,
        m_width,
        m_height
    };
    SDL_Rect frameQuad = {
        m_game_object->xF,
        m_game_object->yF,
        m_width,
        m_height
    };
  
    SDL_RenderCopyEx(Game::instance.canvas(), m_texture, &frameQuad, &renderQuad, 0, 0, SDL_FLIP_NONE);
}

bool CustomImageComponent::shutdown(){
	ImageComponent::shutdown();
	return true;	
}

void CustomImageComponent::setWidth(double width){
	m_width = width;
}
void CustomImageComponent::setHeight(double height){
    m_height = height;
}