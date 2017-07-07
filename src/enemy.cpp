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
    
    setTilemap();
    minimumPath(pos);
    discoverNextMove();
    makeNextMove();

    return true;
}

void Enemy::hold() {
	cout << "PAROU O BIXAO" << endl;
	int componentX = 0;
    int componentY = 0;

    Vector2D move(componentX,componentY);
    physics.velocity = move;
}

void Enemy::moveDown(){
	cout << "BAIXO O BIXAO" << endl;
    // Update Velocity
    int componentX = 0;
    int componentY = defaultVel;

    Vector2D move(componentX,componentY);
    physics.velocity = move;
}

void Enemy::moveUp() {
	cout << "CIMA O BIXAO" << endl;
    // Update Velocity
    int componentX = 0;
    int componentY = -1*defaultVel;

    Vector2D move(componentX,componentY);
    physics.velocity = move;
}

void Enemy::moveLeft() {
	cout << "ESQUERDA O BIXAO" << endl;
    // Update Velocity
    int componentX = -1*defaultVel;

    int componentY = 0;

    Vector2D move(componentX,componentY);
    physics.velocity = move;
}

void Enemy::moveRight() {
	cout << "DIREITA O BIXAO" << endl;
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


void Enemy::minimumPath(Vector2D pos){
	using ii = pair<int, int>;
	using iii = pair <ii, int>;

	ii posTarget = ii(pos.getY()/32, pos.getX()/32);
	ii posEnemy = ii(positionY/32, positionX/32);

	cout<<"X Enemy: " << posEnemy.first << " Y Enemy: "<<posEnemy.second<<endl;
    cout<<"X Player: " << posTarget.first << " Y Player: "<<posTarget.second<<endl;

	if (matrix[posTarget.first][posTarget.second] == 1) {
		queue<ii> q;
		q.push(posTarget);

		while(!q.empty()) {
	    	ii v = q.front();
	    	q.pop();

	    	if(matrix[v.first][v.second] == 0) {
	    		posTarget.first = v.first;
	    		posTarget.second = v.second;
	    		break;
	    	}

	    	if(v.second > 0 && v.second < 32) {
				q.push(ii(v.first, v.second - 1));
				q.push(ii(v.first, v.second + 1));
			}
			if(v.first > 0 && v.first < 22) {
				q.push(ii(v.first - 1, v.second));
				q.push(ii(v.first + 1, v.second));
			}
	    }
	}

	for (int i=0; i<22; i++){
		for (int j=0; j<32; j++){
			matrixAux[i][j] = matrix[i][j];
		}
	}

    matrixAux[posEnemy.first][posEnemy.second] = 2;

    queue<iii> q;
    q.push(iii(posEnemy, 2));

    while(!q.empty()) {
    	iii v = q.front();
    	q.pop();

    	//cout<<v.first.first << " " << v.first.second << endl;
    	//cout<<posTarget.first<<" " << posTarget.second <<endl;

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

    int i = posTarget.first, j = posTarget.second;
    int distPlayer = matrixAux[i][j];
    distance = distPlayer;

    memset(matrixMinimumPath, 0, sizeof matrixMinimumPath);

    matrixMinimumPath[i][j] = 1;

    do {
    	if(matrixAux[i][j - 1] == distPlayer - 1) {
    		distPlayer--;
    		matrixMinimumPath[i][j-1] = 1;
    		j = j - 1;
    	}
    	else if(matrixAux[i][j + 1] == distPlayer - 1) {
    		distPlayer--;
    		matrixMinimumPath[i][j+1] = 1;
    		j = j + 1;
    	}
    	else if(matrixAux[i - 1][j] == distPlayer - 1) {
    		distPlayer--;
    		matrixMinimumPath[i-1][j] = 1;
    		i = i - 1;
    	}
    	else if(matrixAux[i + 1][j] == distPlayer - 1) {
    		distPlayer--;
    		matrixMinimumPath[i+1][j] = 1;
    		i = i + 1;
    	}
    	if(distPlayer == 2)
    		matrixMinimumPath[i][j] = 1;
    } while (distPlayer > 2);

    while(!q.empty()) q.pop();
}

//0 Parado, 1 Esquerda, 2 Direita, 3 Cima, 4 Baixo

void Enemy::discoverNextMove() {
	using ii = pair<int, int>;

	ii posEnemy = ii(positionY/32, positionX/32);

	if(distance >= 15 || !canMove) {
		nextMove = 0;
	}

	else if(distance <= 2) {
		nextMove = 1;
	}

	//Esquerda

	else if(matrixMinimumPath[posEnemy.first][posEnemy.second - 1] == 1) {
		nextMove = 1;
	}

	//Direita

	else if(matrixMinimumPath[posEnemy.first][posEnemy.second + 1] == 1) {
		nextMove = 2;
	}

	//Cima

	else if(matrixMinimumPath[posEnemy.first - 1][posEnemy.second] == 1) {
		nextMove = 3;
	}

	//Baixo

	else if(matrixMinimumPath[posEnemy.first + 1][posEnemy.second] == 1) {
		nextMove = 4;
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