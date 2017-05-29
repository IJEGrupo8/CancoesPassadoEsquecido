#include "tileset.hpp"
#include "components/image.hpp"
#include "game.hpp"
#include "log.h"

using namespace engine;


bool TileSet::init(){
	INFO("Init Tileset");

	ImageComponent::init();

	m_rows = m_game_object->h / m_height;
	m_columns = m_game_object->w / m_width;
	
	return true;
}

void TileSet::render(int index, int x, int y){
	if(index >= m_rows * m_columns){
		exit(1);
	}

	//INFO("x  " << x << "y  "<< y);

	int xx = (index % m_columns) * m_width;
	int yy = (index / m_columns) * m_height;

	//INFO("xx  " << xx << "yy  "<< yy);
	//INFO("w  " << m_width << "h  "<< m_height);


	SDL_Rect clipRect = { xx, yy, m_width, m_height };
	SDL_Rect dstRect = { x, y, clipRect.w, clipRect.h };
	
	SDL_RenderCopyEx(Game::instance.canvas(), m_texture, &clipRect, &dstRect, 0, 0, SDL_FLIP_NONE);
}

int TileSet::getWidth(){
	return m_width;
}

int TileSet::getHeight(){
	return m_height;	
}
