#ifndef __COMPONENTS_TALK_NPC__
#define __COMPONENTS_TALK_NPC__

#include "components/code.hpp"
#include "gameobject.hpp"
#include "player.hpp"
#include "components/text.hpp"
#include "timer.hpp"

using namespace engine;

class TalkNpc : public CodeComponent {
public:
    TalkNpc(GameObject & game_object, TextComponent * _textComponent)
        : CodeComponent(game_object),line(_textComponent){}
        
    TalkNpc() : CodeComponent() {}

    ~TalkNpc() {}
    
    virtual bool update();
    virtual bool init();

    Player * player;
    TextComponent *line;
    Timer timer;

};

#endif