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
    bfs(pos);
    return true;
}

void Enemy::bfs(Vector2D pos){
	using ii = pair<int, int>;
	using iii = pair <ii, int>;

	ii posTarget = ii(pos.getY()/32, pos.getX()/32);
	ii posEnemy = ii(positionY/32, positionX/32);

	cout<<"X Enemy: " << posEnemy.first << " Y Enemy: "<<posEnemy.second<<endl;
    cout<<"X Player: " << posTarget.first << " Y Player: "<<posTarget.second<<endl;

    int matrixAux[22][32];

    cout<<"INIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII"<<endl;

    for (int i=0; i<22; i++){
		for (int j=0; j<32; j++){
			matrixAux[i][j] = matrix[i][j];
			cout << matrixAux[i][j] <<" ";
		}
		cout << endl;
	}

    matrixAux[posEnemy.first][posEnemy.second] = 1;

    queue<iii> q;
    q.push(iii(posEnemy, 1));

    while(!q.empty()) {
    	//cout<<"AAAAAa"<<endl;
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

    while(!q.empty()) q.pop();

    cout<<"FIIIIIIIIIIIIIIIIIIIIIIM"<<endl;

    for (int i=0; i<22; i++){
		for (int j=0; j<32; j++){
			cout << matrixAux[i][j] <<" ";
		}
		cout << endl;
	}
	cout << "FIIIIIIIIIIIIIIIIM2" <<endl;
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

	/*for (int i=0; i<22; i++){
		for (int j=0; j<32; j++){
			cout << matrix[i][j] <<" ";
		}
		cout << endl;
	}*/
}