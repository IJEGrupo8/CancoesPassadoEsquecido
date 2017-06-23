#ifndef __COMPONENTS_TALK_NPC__
#define __COMPONENTS_TALK_NPC__

#include "components/code.hpp"
#include "gameobject.hpp"
#include "player.hpp"
#include "hudbox.hpp"
#include "components/image.hpp"
#include "components/text.hpp"
#include "timer.hpp"

using namespace engine;

class TalkNpc : public CodeComponent {
public:
    TalkNpc(GameObject & game_object, HUDBox * _box)
        : CodeComponent(game_object),box(_box){}
        
    TalkNpc() : CodeComponent() {}

    ~TalkNpc() {}
    
    virtual bool update();
    virtual bool init();

    Player * player;
    HUDBox * box;
    ImageComponent *box_image;
    TextComponent *line;
    Timer timer;

};

#endif