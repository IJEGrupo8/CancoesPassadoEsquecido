#include "tileset.hpp"
#include "components/image.hpp"
#include "game.hpp"
#include "log.h"

using namespace engine;

TileSet::TileSet(int width, int height, GameObject & game_object, std::string path,int m_i, int m_j){
	m_game_object = &game_object;
	m_path = path;
	m_i = m_i;
	m_j = m_j;
	m_width = width;
	m_height = height;
	m_state = State::enabled;
}

TileSet::~TileSet(){
	//delete(&tileset);
}
bool TileSet::init(){
	INFO("Init Tileset");

	ImageComponent::init();
	rows = m_game_object->h / m_height;
	columns = m_game_object->w / m_width;

	INFO("rows = " << rows << " " << columns);
	
	return true;
}
void TileSet::render(int index, int x, int y){
	if(index >= rows * columns){
		exit(1);
	}

	int xx = (index % columns) * m_width;
	int yy = (index / columns) * m_height;

	SDL_Rect *clipRect = new SDL_Rect { xx, yy, m_width, m_height };
	SDL_Rect *dstRect = new SDL_Rect{ x, y, clipRect->w, clipRect->h };

	SDL_RenderCopyEx(Game::instance.canvas(), m_texture, clipRect, dstRect, 0, 0, SDL_FLIP_NONE);
}

int TileSet::getWidth(){
	return m_width;
}

int TileSet::getHeight(){
	return m_height;	
}
