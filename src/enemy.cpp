#include "log.h"
#include "enemy.hpp"
#include "tilemap.hpp"
#include "gamescene.hpp"

using namespace std;

bool Enemy::init()
{
    engine::GameObject::init();
    return true;
}

bool Enemy::shutdown()
{
    engine::GameObject::shutdown();
    return true;
}

bool Enemy::draw()
{
    engine::GameObject::draw();
    return true;
}

bool Enemy::update()
{
    engine::GameObject::update();

    positionX = physics.position.getX();
    positionY = physics.position.getY();

    cout<<"X Enemy: " << positionX/32 << " Y Enemy: "<<positionY/32<<endl;

    setTilemap();
    return true;
}


void Enemy::setTilemap(){

	auto tilemap_as_game_object = (dynamic_cast<GameScene *>(Game::instance.m_scene))->get_active_room()->get_game_object("mapa");
	auto tilemap = (dynamic_cast<TileMap *>(tilemap_as_game_object));
	int k = 22*32 + 22*32;

	cout << tilemap->tile_matrix.size()<<endl;

	for (int i=0; i<22; i++){
		for (int j=0; j<32; j++){
			matrix[i][j] = tilemap->tile_matrix[k++];
		}
	}

	for (int i=0; i<22; i++){
		for (int j=0; j<32; j++){
			cout << matrix[i][j] <<" ";
		}
		cout << endl;
	}
}