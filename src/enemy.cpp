#include "log.h"
#include "enemy.hpp"
#include "tilemap.hpp"
#include "gamescene.hpp"
#include "components/animationcontroller.hpp"
#include "components/animation.hpp"
#include "gameglobals.hpp"
#include <queue>

using namespace std;

bool Enemy::init()
{
    engine::GameObject::init();
    moveDownA->init();

    activeAnimation = moveDownA;

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
    activeAnimation->draw(); 
    return true;
}

bool Enemy::update()
{
    engine::GameObject::update();
    activeAnimation->update();

    positionX = physics.position.getX();
    positionY = physics.position.getY();

    Vector2D pos = m_target->physics.position;
    
    distance = hypot(pos.getX()/32 - physics.position.getX()/32, 
                         pos.getY()/32 - physics.position.getY()/32);

    setTilemap();

	discoverNextMove(pos);

    makeNextMove();

    return true;
}

void Enemy::hold() {
	int componentX = 0;
    int componentY = 0;

    Vector2D move(componentX,componentY);
    physics.velocity = move;
}

void Enemy::moveDown(){
    // Update Velocity
    int componentX = 0;
    int componentY = defaultVel;

    Vector2D move(componentX,componentY);
    physics.velocity = move;

}

void Enemy::moveUp() {
    // Update Velocity
    int componentX = 0;
    int componentY = -1*defaultVel;

    Vector2D move(componentX,componentY);
    physics.velocity = move;
}

void Enemy::moveLeft() {
    // Update Velocity
    int componentX = -1*defaultVel;

    int componentY = 0;

    Vector2D move(componentX,componentY);
    physics.velocity = move;

}

void Enemy::moveRight() {
    // Update Velocity

    int componentX = defaultVel;
    int componentY = 0;

    Vector2D move(componentX,componentY);
    physics.velocity = move;
}

void Enemy::makeNextMove() {
	//0 Parado, 1 Esquerda, 2 Direita, 3 Cima, 4 Baixo

    switch (nextMove) {
    	case 0:
    		hold();
    	break;
    	case 1:
    		moveLeft();
    	break;
    	case 2:
    		moveRight();
    	break;
    	case 3:
    		moveUp();
    	break;
    	case 4:
    		moveDown();
    	break;
    }
}


//0 Parado, 1 Esquerda, 2 Direita, 3 Cima, 4 Baixo

void Enemy::discoverNextMove(Vector2D pos) {
	using ii = pair<int, int>;

	ii posEnemy = ii(positionY/32, positionX/32);
	ii posTarget = ii(pos.getY()/32, pos.getX()/32);

	int i = posTarget.first, j = posTarget.second;
	int z = posEnemy.first, q = posEnemy.second;


	if(distance >= 100 || !canMove) {
		nextMove = 0;
	}

	else if(distance <= 2) {
		nextMove = nextMove;
	}

	//Esquerda

	else if(hypot(i - z, j - q - 1) <= distance) {
		nextMove = 2;
	}

	//Direita

	else if(hypot(i - z, j - q + 1) <= distance) {
		nextMove = 1;
	}

	//Cima

	else if(hypot(i - z - 1, j - q) <= distance) {
		nextMove = 4;
	}

	//Baixo

	else if(hypot(i - z + 1, j - q) <= distance) {
		nextMove = 3;
	}

	//Parado

	else {
		nextMove = 0;
	}
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
}

int Enemy::getEnemyType(){
    return m_enemy_type;
}