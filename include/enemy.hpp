#ifndef __GAME_ENEMY_OBJECT__
#define __GAME_ENEMY_OBJECT__

#include <string>
#include "gameobject.hpp"
#include "components/image.hpp"
#include "customimagecomponent.hpp"
#include "player.hpp"


using namespace engine;

class Enemy : public GameObject {
public:
    Enemy() : GameObject() {}
    Enemy(std::string _name,int _x,int _y)
        : GameObject(_name,_x,_y) {}
 	
 	~Enemy() {}
    virtual bool init();
    virtual bool shutdown();
    virtual bool update();
    virtual bool draw();
 	void setTilemap();

    int life = 100;
    bool canMove = true;
    int matrix[32][32];
    int positionX, positionY;


private:

};

#endif
