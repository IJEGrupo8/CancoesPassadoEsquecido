#include "gamescene.hpp"
#include "scene.hpp"
#include "log.h"
#include <string>
#include "keyword.hpp"
#include "player.hpp"

using namespace engine;

Player *player1;
//Player *player2;

bool GameScene::init(){
    Scene::init();

    player1 = (dynamic_cast<Player *>(m_objects["Player1"]));

    //player2 = (dynamic_cast<Player *>(m_objects["Player2"]));
}

bool GameScene::handlePlayer1(){
    bool keyFlag = false;
    //bool collision = player1->physics.detectColision(player2);
    if(Input::keyPressed(Input::UP))
    {
        player1->moveUp();
        keyFlag = true;
    }
    if(Input::keyPressed(Input::DOWN))
    {
        player1->moveDown();

        keyFlag = true;
    }
    if(Input::keyPressed(Input::RIGHT))
    {
        player1->moveRight();

        keyFlag = true;
    }
    if(Input::keyPressed(Input::LEFT))
    {
        player1->moveLeft();
        keyFlag = true;
    }

    
    /*if(keyFlag){
        
        if(collision) {
            player1->physics.velocity-=  player1->physics.collisionObj*3;
            INFO("Colidindo");
        }
        
    }*/
    if(!keyFlag){
        Vector2D nulo(0,0);
        player1->physics.velocity = nulo;
    }
    return true;
}



bool GameScene::update()
{
    handlePlayer1();
    
    Scene::update();

    return true;
}

bool GameScene::draw()
{
    Scene::draw();
    m_objects["Player1"]->draw();

    return true;
}