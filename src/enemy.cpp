#include "log.h"
#include "enemy.hpp"
#include "tilemap.hpp"
#include "gamescene.hpp"
#include <queue>

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

    Vector2D pos = m_target->physics.position;
    
    distance = hypot(pos.getX() - physics.position.getX(), 
                         pos.getY() - physics.position.getY());

    bool hasMinimum = true;

    if(updateFrame == 5) {
    	updateFrame = 0;
    	if (distance < 300) {
    		setTilemap();
	    	hasMinimum = minimumPath(pos);
    	}
	    if(hasMinimum) {
	    	discoverNextMove(pos);
	    }
    }

    makeNextMove();

	updateFrame++;

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


bool Enemy::minimumPath(Vector2D pos){
	using ii = pair<int, int>;
	using iii = pair <ii, int>;

	ii posTarget = ii(pos.getY()/32, pos.getX()/32);
	ii posEnemy = ii(positionY/32, positionX/32);

	cout<<"X Enemy: " << posEnemy.first << " Y Enemy: "<<posEnemy.second<<endl;
    cout<<"X Player: " << posTarget.first << " Y Player: "<<posTarget.second<<endl;

	for (int i=0; i<22; i++){
		for (int j=0; j<32; j++){
			matrixAux[i][j] = matrix[i][j];
		}
	}

	if (matrix[posTarget.first][posTarget.second] == 1) {
		nextMove = 0;
		return false;
	}

    matrixAux[posEnemy.first][posEnemy.second] = 2;

    queue<iii> q;
    q.push(iii(posEnemy, 2));

    while(!q.empty()) {
    	iii v = q.front();
    	q.pop();

    	if(v.first.first == posTarget.first && v.first.second == posTarget.second) {
    		break;
    	}

    	if(v.first.first >= 0 && v.first.first <= 22 && v.first.second >= 0 && v.first.second <= 32) {
			if(v.first.second > 0 && matrixAux[v.first.first][v.first.second - 1] == 0) {
				q.push(iii(ii(v.first.first, v.first.second - 1), v.second + 1));
				matrixAux[v.first.first][v.first.second - 1] = v.second + 1;
			}
			if(v.first.second < 32 && matrixAux[v.first.first][v.first.second + 1] == 0) {
				q.push(iii(ii(v.first.first, v.first.second + 1), v.second + 1));
				matrixAux[v.first.first][v.first.second + 1] = v.second + 1;
			}
			if(v.first.first > 0 && matrixAux[v.first.first - 1][v.first.second] == 0) {
				q.push(iii(ii(v.first.first - 1, v.first.second), v.second + 1));
				matrixAux[v.first.first - 1][v.first.second] = v.second + 1;
			}
			if(v.first.first < 22 && matrixAux[v.first.first + 1][v.first.second] == 0) {
				q.push(iii(ii(v.first.first + 1, v.first.second), v.second + 1));
				matrixAux[v.first.first + 1][v.first.second] = v.second + 1;
			}
		}
	}

    return true;
} 

//0 Parado, 1 Esquerda, 2 Direita, 3 Cima, 4 Baixo

void Enemy::discoverNextMove(Vector2D pos) {
	using ii = pair<int, int>;

	ii posEnemy = ii(positionY/32, positionX/32);
	ii posTarget = ii(pos.getY()/32, pos.getX()/32);

	int i = posTarget.first, j = posTarget.second;
    int distPlayer = matrixAux[i][j];

	if(distance >= 300 || !canMove) {
		nextMove = 0;
	}

	else if(distance <= 10) {
		nextMove = nextMove;
	}

	//Esquerda

	else if(matrixAux[i][j - 1] == distPlayer - 1 && matrix[i][j-1] != 1) {
		nextMove = 2;
	}

	//Direita

	else if(matrixAux[i][j + 1] == distPlayer - 1  && matrix[i][j+1] != 1) {
		nextMove = 1;
	}

	//Cima

	else if(matrixAux[i - 1][j] == distPlayer - 1  && matrix[i-1][j] != 1) {
		nextMove = 4;
	}

	//Baixo

	else if(matrixAux[i + 1][j] == distPlayer - 1  && matrix[i+1][j] != 1) {
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