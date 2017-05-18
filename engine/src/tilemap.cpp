#include "tilemap.hpp"
#include "tileset.hpp"
#include "vector.hpp"
#include <string>
#include <fstream>
#include <sstream>
#include "log.h"

using namespace engine;

/*TileMap::~TileMap(){
	delete(m_tileset);
}*/

bool TileMap::init(){
	//Aqui ja nao ta mais enabled
	TileSet tileset(m_width, m_height, *this, m_map_path, 1, 1);
	setTileSet(&tileset);
	add_component(tileset);

    if(m_tileset->state() == Component::State::enabled)
    	INFO("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
	INFO("Init Tilemap");

	std::fstream f(m_map_path, f.in);

	if(not f.is_open()){
		exit(1);
	}else{
		std::string s;
		getline(f, s);

		std::stringstream ss;
		ss << s;

		ss >> map_width;
		ss.ignore(2, ',');

		ss >> map_height;
		ss.ignore(2, ',');

		ss >> map_depth;
		ss.ignore(2, ',');

		while(getline(f, s)){
			ss.clear();
			ss << s;

			int index;
			while(ss >> index){
				tile_matrix.emplace_back(--index);

				ss.ignore(2, ',');
			}
		}
	}

	GameObject::init();

	return true;
}

void TileMap::setTileSet(TileSet *tSet){
	m_tileset = tSet;
}

int &TileMap::at(int x, int y, int z){
	int index = (y * map_width + x) + (z * map_width * map_height);
	return tile_matrix[index];
}

void TileMap::renderLayer(int layer, int camera_x, int camera_y){
	for(int y = 0; y < map_height; y++){
		for(int x = 0; x < map_width; x++){
			m_tileset->render(at(x, y, layer), x * m_tileset->getWidth() + camera_x, 
			y * m_tileset->getHeight() + camera_y);
		}
	}
}

bool TileMap::draw(){
	INFO("Draw Tilemap  ");
	for(int layer = 0; layer < map_depth; layer++){
		INFO("Draw LAYER " << layer);
		renderLayer(layer, 0, 0);
	}

	return true;
}