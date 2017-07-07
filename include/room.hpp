#ifndef __ROOM_SCENE__
#define __ROOM_SCENE__

#include <string>
#include <unordered_map>

#include "scene.hpp"
#include "components/changeroom.hpp"

using namespace engine;

class Room : public Scene{
public:

    Room() : Scene("") {}
    Room(std::string _name)
        : Scene(_name) {}

    ~Room() {}
    bool draw();
    bool update();
    bool init();
    bool add_enemy(std::string enemy_id, int x, int y);
    bool add_room_transition(std::string id_transition, int x, int y,
         int w, int h, std::string target_room, ChangeRoom::Direction direction);

private:
/*
    virtual bool init();
    virtual bool shutdown();
    virtual bool draw();
    virtual
    virtual bool verifyColision(GameObject* ob);
*/


};

#endif
