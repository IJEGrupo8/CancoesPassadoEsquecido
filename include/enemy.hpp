#ifndef __GAME_ENEMY_OBJECT__
#define __GAME_ENEMY_OBJECT__

#include <string>
#include "gameobject.hpp"
#include "components/image.hpp"
#include "customimagecomponent.hpp"
#include "player.hpp"
#include "components/animation.hpp"


using namespace engine;

class Enemy : public GameObject {
public:
    Enemy() : GameObject() {}
    Enemy(std::string _name, int _x, int _y, Player * target, int enemy_life, int enemy_type)
        : GameObject(_name,_x,_y), m_target(target), life(enemy_life), m_enemy_type(enemy_type) {}
 	
 	~Enemy() {}
    virtual bool init();
    virtual bool shutdown();
    virtual bool update();
    virtual bool draw();
 	void setTilemap();
    bool minimumPath(Vector2D pos);
    void discoverNextMove(Vector2D pos);
    void hold();
    void moveDown();
    void moveUp();
    void moveLeft();
    void moveRight();
    void makeNextMove();
    int getEnemyType();

    int life;
    AnimationComponent *moveRightA, *moveLeftA, *moveUpA, *moveDownA, *activeAnimation;
    bool canMove = true;
    float defaultVel = 3;



private:
    Player* m_target;
    int distance;
    int m_enemy_type;
    int updateFrame = 5;
    int matrix[22][32];
    int positionX, positionY;
    //0 Parado, 1 Esquerda, 2 Direita, 3 Cima, 4 Baixo
    int nextMove = 0;
    

};

#endif
