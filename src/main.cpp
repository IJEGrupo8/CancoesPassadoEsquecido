#include "game.hpp"
#include "gameobject.hpp"
#include "scene.hpp"
#include "components/image.hpp"
#include "components/text.hpp"
#include "components/audio.hpp"
#include "components/animation.hpp"
#include "components/moveDirectionals.hpp"
#include "components/moveSS.hpp"
#include "components/follow.hpp"
#include "components/animationcontroller.hpp"
#include "components/changeroom.hpp"
#include "player.hpp"
#include "gamescene.hpp"
#include "menuscene.hpp"
#include "spell.hpp"

#include "gameglobals.hpp"

using namespace std;
using namespace engine;

int main(int, char**)
{
    // Configure game
    Game::instance.set_properties(globals::game_name, globals::window_size);

    // Setup scenes
    GameScene room1("stage_1_room_1");
    GameScene room2("stage_2_room_2");
    room1.right = &room2;
    room2.left = &room1;
    /*MenuScene menu("Menu");
    
    Game::instance.add_scene(menu);
    
    GameObject playbutton("playbutton",200,200);
    ImageComponent playImage(playbutton,"assets/sprites/playbutton.png",1,1);
    playbutton.add_component(playImage);
    menu.add_game_object(playbutton);
*/
    /* Gamescene*/
    Game::instance.add_scene(room1);

    Player player("Player1",100,100);
    player.xF = 0; player.yF = 0;

    MoveDirectionals move(player);

    //Declaring instruments
    Instrument banjo("Banjo", 100,100);
    Instrument eletric_guitar("Eletric Guitar", 100,100);
    Instrument accordion("Accordion", 100,100);
    //Declaring spells
    Spell spellQBanjo("spellQBanjo",&player,0,0,5000,5000);
    Spell spellWBanjo("spellWBanjo",&player,0,0,5000,5000);
    Spell spellEBanjo("spellEBanjo",&player,0,0,5000,1000);

    spellQBanjo.xF = 0; spellQBanjo.yF = 0;
    spellWBanjo.xF = 0; spellWBanjo.yF = 0;
    spellEBanjo.xF = 0; spellEBanjo.yF = 0;

    //Adicionando imagem ao spell

    AnimationComponent explosionQImage(spellQBanjo, "explosion.png", 4, 4,5000,0,15);
    AnimationComponent explosionWImage(spellWBanjo, "explosion.png", 4, 4,500,0,15,4);
    AnimationComponent explosionEImage(spellEBanjo, "explosion.png", 4, 4,1000,0,15);

    //AnimationControllerComponent explosionController();

    spellQBanjo.add_component(explosionQImage);
    spellWBanjo.add_component(explosionWImage);
    spellEBanjo.add_component(explosionEImage);  

    //Adicionando spell ao instrumento
    banjo.addSpell(globals::spellQ,&spellQBanjo);
    banjo.addSpell(globals::spellW,&spellWBanjo);
    banjo.addSpell(globals::spellE,&spellEBanjo);
    //spell[globals::spellQ]
    player.addInstrument(globals::banjo, banjo);
    player.addInstrument(globals::eletric_guitar, eletric_guitar);
    player.addInstrument(globals::accordion, accordion);

    ImageComponent banjoImage(player, "girl2.png", 4, 4);
    ImageComponent eletricGuitarImage(player, "girl3.png", 4, 4);
    ImageComponent accordionImage(player, "girl4.png", 4, 4);

    player.addSprite(globals::banjo, &banjoImage);
    player.addSprite(globals::eletric_guitar, &eletricGuitarImage);
    player.addSprite(globals::accordion, &accordionImage);

    player.add_component(banjoImage);
    player.add_component(eletricGuitarImage);
    player.add_component(accordionImage);
    player.add_component(move);
    //ghost
    GameObject ghost("ghost", 800, 200);
    ghost.xF = 0; ghost.yF = 0;
    AnimationComponent ghostI(ghost, "ghost.png", 4, 4, 500, 0,3 ,-1);
    FollowPlayer moveGhost(ghost);
    AnimationControllerComponent ghostController(ghost);
    ghostController.addAnimation("moveDown", ghostI);

    ghost.add_component(ghostController);
    ghost.add_component(moveGhost);
    //change room handler
    GameObject goRight("goRight", 200,200);
    goRight.xF = 0; goRight.yF = 0;

    ChangeRoom goRightComponent(goRight,ChangeRoom::Direction::right);
    ImageComponent wayout(goRight, "playbutton.png", 1, 1);
    goRight.add_component(goRightComponent); 
    goRight.add_component(wayout); 
    //add to scene
    room1.add_game_object(spellWBanjo);
    room1.add_game_object(spellEBanjo);
    room1.add_game_object(spellQBanjo);
    room1.add_game_object(accordion);
    room1.add_game_object(eletric_guitar);
    room1.add_game_object(banjo);
    room1.add_game_object(player);
    room1.add_game_object(ghost);
    room1.add_game_object(goRight);

    // Game loop
    Game::instance.run();
    return 0;
}
