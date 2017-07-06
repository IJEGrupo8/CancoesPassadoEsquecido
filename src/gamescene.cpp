#include "gamescene.hpp"
#include "scene.hpp"
#include "log.h"
#include <string>
#include "keyword.hpp"
#include "player.hpp"

using namespace engine;

bool GameScene::init(){

    Scene::init();
    for (auto room: rooms)
    {
        auto obj = room.second;
        //obj->resetState();
        if (obj->init() == false) return false;
    }
    return true;
}

bool GameScene::update()
{
    Scene::update();
    active_room->update();
    return true;
}

bool GameScene::draw()
{
    active_room->draw();
    Scene::draw();
    if(active_room == NULL){
        WARN("ACTIVE ROOM IS NULL");
        return false;
    }

    return true;
}
void GameScene::add_room(std::string room_name)
{
    if(rooms[room_name] == NULL){
        Room * newRoom = new Room(room_name);
        rooms[room_name] = newRoom;

        if(rooms.size() == 1) active_room = newRoom;
    }else{
        WARN("Room "<<room_name<<" already exists");
        return;
    }
}

void GameScene::add_game_object_to_room(std::string room_id, GameObject & obj)
{
    if(rooms.find(room_id) != rooms.end()){
      //INFO("ADDED");
      rooms[room_id]->add_game_object(obj);
    }else{
      WARN("room "<< room_id<< " Not found");
    }
}

Room * GameScene::get_room(std::string room_id)
{
    return rooms[room_id];
}

Room * GameScene::get_active_room()
{
    return active_room;
}

bool GameScene::change_room(std::string room_id)
{
  if(rooms.find(room_id) != rooms.end())
  {
    active_room = rooms[room_id];
    return true;
  }
  else
  {
    WARN("Room_id invalid " <<room_id);
    return false;
  }
}
