#ifndef __GAME_SCENE__
#define __GAME_SCENE__

#include <string>
#include <unordered_map>

#include "room.hpp"
#include "scene.hpp"

using namespace engine;

class GameScene : public Scene{
public:

    GameScene() : Scene("") {}
    GameScene(std::string _name)
        : Scene(_name) {}

    ~GameScene() {}

    bool draw();
    bool update();
    bool init();

    void add_room(std::string name_room);
    void add_game_object_to_room(std::string room_id, GameObject & obj);
    Room * get_room(std::string room_id);
    Room * get_active_room();
    bool change_room(std::string room_id);


private:
  std::unordered_map<std::string, Room *> rooms;
  Room * active_room;

/*
    virtual bool init();
    virtual bool shutdown();
    virtual bool draw();
    virtual
    virtual bool verifyColision(GameObject* ob);
*/


};

#endif
