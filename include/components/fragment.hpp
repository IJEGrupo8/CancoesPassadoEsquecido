#ifndef __COMPONENTS_FRAGMENT__
#define __COMPONENTS_FRAGMENT__


#include "components/code.hpp"
#include "gameobject.hpp"

using namespace engine;

class FragmentComponent : public CodeComponent {
public:
    FragmentComponent(GameObject & game_object, int _id)
        : CodeComponent(game_object),id(_id) {}
        
    FragmentComponent() : CodeComponent() {}

    ~FragmentComponent() {}
    
    virtual bool update();
    virtual bool init();
    GameObject * player;
    int id;
    //Timer timer;

};

#endif