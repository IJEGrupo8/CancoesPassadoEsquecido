#ifndef __ROOM_SCENE___
#define __ROOM_SCENE__

#include <string>
#include <unordered_map>

#include "scene.hpp"

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
