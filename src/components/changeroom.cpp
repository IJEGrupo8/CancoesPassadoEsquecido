#include "log.h"
#include "components/changeroom.hpp"
#include "vector.hpp"
#include "game.hpp"
#include "gamescene.hpp"
#include "gameglobals.hpp"


bool ChangeRoom::init(){
    //m_game_object->physics.velocity.setY(3);
    INFO("Init changeroom");

    return true;
}

bool ChangeRoom::update(){
    m_game_object->physics.collisionBox.x = m_game_object->physics.position.getX();
    m_game_object->physics.collisionBox.y = m_game_object->physics.position.getY();
    m_game_object->physics.collisionBox.w = m_game_object->w;
    m_game_object->physics.collisionBox.h = m_game_object->h;

    player = Game::instance.m_scene->get_game_object("Player1");

    if(m_game_object->physics.detectColision(player))
    {
        (dynamic_cast<GameScene *>(Game::instance.m_scene))->change_room(room_name);
        if(dir == Direction::Right)
        {
            INFO("DIRECTION  RIGHT");
            player->physics.position.setX(globals::window_size.first
                - player->physics.position.getX() + 1);
            player->physics.position.setY(330);
        }
        else if(dir == Direction::Left)
        {
            player->physics.position.setX(globals::window_size.first
                - player->physics.position.getX() - 100);
        }
        else if(dir == Direction::Botton)
        {
            player->physics.position.setY(globals::window_size.first
                - player->physics.position.getY() - 325);
        }
        else if(dir == Direction::Top)
        {
            player->physics.position.setY(globals::window_size.first
                - player->physics.position.getY() - 350);

        }
    }
    return true;
}
