#include "game.hpp"
#include "gameobject.hpp"
#include "scene.hpp"
#include "components/image.hpp"
#include "components/text.hpp"
#include "components/audio.hpp"
#include "components/animation.hpp"
#include "components/moveDirectionals.hpp"
#include "components/moveSS.hpp"
#include "components/damageEnemy.hpp"
#include "components/follow.hpp"
#include "components/animationcontroller.hpp"
#include "components/changeroom.hpp"
#include "components/fragment.hpp"
#include "components/pushenemy.hpp"
#include "basicspell.hpp"
#include "customimagecomponent.hpp"
#include "player.hpp"
#include "gamescene.hpp"
#include "menuscene.hpp"
#include "gameover.hpp"
#include "spell.hpp"
#include "tilemap.hpp"
#include "tileset.hpp"
#include "log.h"
#include "gameglobals.hpp"
#include "hudlife.hpp"
#include "hudinstrument.hpp"
#include "enemy.hpp"

using namespace std;
using namespace engine;

int main(int, char**)
{
    // Configure game
    Game::instance.set_properties(globals::game_name, globals::window_size);

    // Setup scenes
    MenuScene menu("Menu");
    MenuScene GameoverScene("Gameover");
    MenuScene VictoryScene("Victory");
    GameScene room1("stage_1_room_1");
    GameScene room2("stage_1_room_2");
    GameScene room3("stage_1_room_3");
    GameScene room4("stage_1_room_4");
    GameScene room5("stage_1_room_5");

    /* Gamescene*/
    Game::instance.add_scene(menu);
    Game::instance.add_scene(room1);
    Game::instance.add_scene(room2);
    Game::instance.add_scene(room3);
    Game::instance.add_scene(room4);
    Game::instance.add_scene(room5);
    Game::instance.add_scene(GameoverScene);
    Game::instance.add_scene(VictoryScene);

    Player player(globals::player,100,100);
    player.xF = 0; player.yF = 0;

    //Declaring instruments
    Instrument banjo(globals::banjo, 100,100);
    Instrument eletric_guitar(globals::eletric_guitar, 100,100);
    Instrument accordion(globals::accordion, 100,100);
    //Declaring spells
    BasicSpell spellQBanjo("spellQBanjo",&player,0,0,1500,1500);
    BasicSpell spellQGuitar("spellQGuitar",&player,0,0,1500,1500);
    BasicSpell spellQAccordion("spellQAccordion",&player,0,0,1500,1500);

    spellQBanjo.xF = 0; spellQBanjo.yF = 0;
    spellQGuitar.xF = 0; spellQGuitar.yF = 0;
    spellQAccordion.xF = 0; spellQAccordion.yF = 0;

    AudioComponent somQBanjo(spellQBanjo,"drumsBasic.wav",false,false);
    AudioComponent somQGuitar(spellQGuitar,"drumsBasic.wav",false,false);
    AudioComponent somQAccordion(spellQAccordion,"drumsBasic.wav",false,false);

    ImageComponent banjoQImage(spellQBanjo, "musicnote.png", 3, 3);
    ImageComponent guitarQImage(spellQGuitar, "musicnote.png", 3, 3);
    ImageComponent accordionQImage(spellQAccordion, "musicnote.png", 3, 3);

    //AnimationControllerComponent explosionController();

    spellQBanjo.add_component(banjoQImage);
    spellQBanjo.add_component(somQBanjo);

    spellQGuitar.add_component(guitarQImage);
    spellQGuitar.add_component(somQGuitar);

    spellQAccordion.add_component(accordionQImage);
    spellQAccordion.add_component(somQGuitar);

    //Adicionando spell ao instrumento
    banjo.addSpell(globals::spellQ,&spellQBanjo);
    eletric_guitar.addSpell(globals::spellQ,&spellQGuitar);
    accordion.addSpell(globals::spellQ,&spellQAccordion);

    player.addInstrument(globals::banjo, banjo);
    player.addInstrument(globals::eletric_guitar, eletric_guitar);
    player.addInstrument(globals::accordion, accordion);


    HUDInstrument HUDInstrument("hudinstrument", globals::window_size.first-250, globals::window_size.second-120, &player);
    HUDInstrument.xF = 0; HUDInstrument.yF = 0;
    ImageComponent banjoActiveHUD(HUDInstrument, "hud_instruments_0.png", 1, 1);
    ImageComponent eletricGuitarActiveHUD(HUDInstrument, "hud_instruments_1.png", 1, 1);
    ImageComponent accordionActiveHUD(HUDInstrument, "hud_instruments_2.png", 1, 1);

    HUDInstrument.addHUD(globals::banjo, &banjoActiveHUD);
    HUDInstrument.addHUD(globals::eletric_guitar, &eletricGuitarActiveHUD);
    HUDInstrument.addHUD(globals::accordion, &accordionActiveHUD);

    HUDInstrument.add_component(banjoActiveHUD);
    HUDInstrument.add_component(eletricGuitarActiveHUD);
    HUDInstrument.add_component(accordionActiveHUD);

    //Animation
    AnimationControllerComponent banjoController(player);

    AnimationComponent banjoMoveLeft(player,"walk.png",8,4,2000,0,7,-1);
    AnimationComponent banjoMoveRight(player,"walk.png",8,4,2000,8,15,-1);
    AnimationComponent banjoMoveDown(player,"walk.png",8,4,4000,16,19,-1);
    AnimationComponent banjoMoveUp(player,"walk.png",8,4,4000,24,27,-1);

    banjoController.addAnimation(globals::moveLeft,banjoMoveLeft);
    banjoController.addAnimation(globals::moveRight,banjoMoveRight);
    banjoController.addAnimation(globals::moveDown,banjoMoveDown);
    banjoController.addAnimation(globals::moveUp,banjoMoveUp);

    player.add_component(banjoController);
    player.addSprite(globals::banjo, &banjoController);
    //AnimationComponent ghostI(ghost, "ghost.png", 4, 4, 500, 0, 3 ,-1);

    /*
    ImageComponent banjoImage(player, "girl2.png", 4, 4);
    ImageComponent eletricGuitarImage(player, "girl3.png", 4, 4);
    ImageComponent accordionImage(player, "girl4.png", 4, 4);

    player.addSprite(globals::banjo, &banjoImage);
    player.addSprite(globals::eletric_guitar, &eletricGuitarImage);
    player.addSprite(globals::accordion, &accordionImage);

    player.add_component(banjoImage);
    player.add_component(eletricGuitarImage);
    player.add_component(accordionImage);*/



    MoveDirectionals move(player);
    player.add_component(move);

    GameObject nFragments("nFragments",10,40);
    TextComponent fragmentText(nFragments,"Numero de fragmentos: ","font.ttf",20);
    nFragments.add_component(fragmentText);
    player.nFragments = &fragmentText;

    //ghost1

    Enemy ghost("ghost", 800, 200);
    ghost.xF = 0; ghost.yF = 0;
    AnimationComponent ghostI(ghost, "ghost.png", 4, 4, 500, 0, 3 ,-1);
    FollowPlayer moveGhost(ghost);
    AnimationControllerComponent ghostController(ghost);
    ghostController.addAnimation("moveDown", ghostI);
    DamageEnemy damage(ghost);
    ghost.add_component(damage);
    ghost.add_component(ghostController);
    ghost.add_component(moveGhost);

    //ghost2

    Enemy ghost2("ghost2", 800, 200);
    ghost2.xF = 0; ghost2.yF = 0;
    AnimationComponent ghostI2(ghost2, "ghost.png", 4, 4, 500, 0, 3 ,-1);
    FollowPlayer moveGhost2(ghost2);
    AnimationControllerComponent ghost2Controller(ghost2);
    ghost2Controller.addAnimation("moveDown", ghostI2);
    DamageEnemy damage2(ghost2);
    ghost2.add_component(damage2);
    ghost2.add_component(ghost2Controller);
    ghost2.add_component(moveGhost2);

    //ghost3

    Enemy ghost3("ghost3", 100, 100);
    ghost3.xF = 0; ghost3.yF = 0;
    AnimationComponent ghostI3(ghost3, "ghost.png", 4, 4, 500, 0, 3 ,-1);
    FollowPlayer moveGhost3(ghost3);
    AnimationControllerComponent ghost3Controller(ghost3);
    ghost3Controller.addAnimation("moveDown", ghostI3);
    DamageEnemy damage3(ghost3);
    ghost3.add_component(damage3);
    ghost3.add_component(ghost3Controller);
    ghost3.add_component(moveGhost3);

    //ghosts room 4

    Enemy ghost41("ghost41", 3*32, 3*32);
    ghost41.xF = 0; ghost41.yF = 0;
    AnimationComponent ghostI41(ghost41, "ghost.png", 4, 4, 500, 0, 3 ,-1);
    FollowPlayer moveGhost41(ghost41);
    AnimationControllerComponent ghost41Controller(ghost41);
    ghost41Controller.addAnimation("moveDown", ghostI41);
    DamageEnemy damage41(ghost41);
    ghost41.add_component(damage41);
    ghost41.add_component(ghost41Controller);
    ghost41.add_component(moveGhost41);

    Enemy ghost42("ghost42", 28*32, 3*32);
    ghost42.xF = 0; ghost42.yF = 0;
    AnimationComponent ghostI42(ghost42, "ghost.png", 4, 4, 500, 0, 3 ,-1);
    FollowPlayer moveGhost42(ghost42);
    AnimationControllerComponent ghost42Controller(ghost42);
    ghost42Controller.addAnimation("moveDown", ghostI42);
    DamageEnemy damage42(ghost42);
    ghost42.add_component(damage42);
    ghost42.add_component(ghost42Controller);
    ghost42.add_component(moveGhost42);

    Enemy ghost43("ghost43", 3*32, 19*32);
    ghost43.xF = 0; ghost43.yF = 0;
    AnimationComponent ghostI43(ghost43, "ghost.png", 4, 4, 500, 0, 3 ,-1);
    FollowPlayer moveGhost43(ghost43);
    AnimationControllerComponent ghost43Controller(ghost43);
    ghost43Controller.addAnimation("moveDown", ghostI43);
    DamageEnemy damage43(ghost43);
    ghost43.add_component(damage43);
    ghost43.add_component(ghost43Controller);
    ghost43.add_component(moveGhost43);

    Enemy ghost44("ghost44", 28*32, 15*32);
    ghost44.xF = 0; ghost44.yF = 0;
    AnimationComponent ghostI44(ghost44, "ghost.png", 4, 4, 500, 0, 3 ,-1);
    FollowPlayer moveGhost44(ghost44);
    AnimationControllerComponent ghost44Controller(ghost44);
    ghost44Controller.addAnimation("moveDown", ghostI44);
    DamageEnemy damage44(ghost44);
    ghost44.add_component(damage44);
    ghost44.add_component(ghost44Controller);
    ghost44.add_component(moveGhost44);

    //ghosts room 5

    Enemy ghost51("ghost51", 3*32, 3*32);
    ghost51.xF = 0; ghost51.yF = 0;
    AnimationComponent ghostI51(ghost51, "ghost.png", 4, 4, 500, 0, 3 ,-1);
    FollowPlayer moveGhost51(ghost51);
    AnimationControllerComponent ghost51Controller(ghost51);
    ghost51Controller.addAnimation("moveDown", ghostI51);
    DamageEnemy damage51(ghost51);
    ghost51.add_component(damage51);
    ghost51.add_component(ghost51Controller);
    ghost51.add_component(moveGhost51);

    Enemy ghost52("ghost52", 28*32, 3*32);
    ghost52.xF = 0; ghost52.yF = 0;
    AnimationComponent ghostI52(ghost52, "ghost.png", 4, 4, 500, 0, 3 ,-1);
    FollowPlayer moveGhost52(ghost52);
    AnimationControllerComponent ghost52Controller(ghost52);
    ghost52Controller.addAnimation("moveDown", ghostI52);
    DamageEnemy damage52(ghost52);
    ghost52.add_component(damage52);
    ghost52.add_component(ghost52Controller);
    ghost52.add_component(moveGhost52);

    Enemy ghost53("ghost53", 3*32, 19*32);
    ghost53.xF = 0; ghost53.yF = 0;
    AnimationComponent ghostI53(ghost53, "ghost.png", 4, 4, 500, 0, 3 ,-1);
    FollowPlayer moveGhost53(ghost53);
    AnimationControllerComponent ghost53Controller(ghost53);
    ghost53Controller.addAnimation("moveDown", ghostI53);
    DamageEnemy damage53(ghost53);
    ghost53.add_component(damage53);
    ghost53.add_component(ghost53Controller);
    ghost53.add_component(moveGhost53);

    Enemy ghost54("ghost54", 28*32, 15*32);
    ghost54.xF = 0; ghost54.yF = 0;
    AnimationComponent ghostI54(ghost54, "ghost.png", 4, 4, 500, 0, 3 ,-1);
    FollowPlayer moveGhost54(ghost54);
    AnimationControllerComponent ghost54Controller(ghost54);
    ghost54Controller.addAnimation("moveDown", ghostI54);
    DamageEnemy damage54(ghost54);
    ghost54.add_component(damage54);
    ghost54.add_component(ghost54Controller);
    ghost54.add_component(moveGhost54);


    //change room handler
    GameObject goRightRoom1("goRightRoom1", 925,200);
    goRightRoom1.xF = 0; goRightRoom1.yF = 0;
    ChangeRoom goRightRoom1Component(goRightRoom1,room2.name(),ChangeRoom::Direction::Right);
    goRightRoom1.add_component(goRightRoom1Component);
    goRightRoom1.w = 100; goRightRoom1.h = 100;

    GameObject goLeftRoom2("goLeftRoom2", 0, 320);
    goLeftRoom2.xF = 0; goLeftRoom2.yF = 0;
    goLeftRoom2.w = 100; goLeftRoom2.h = 100;
    ChangeRoom goLeftRoom2Component(goLeftRoom2, room1.name(), ChangeRoom::Direction::Left);
    goLeftRoom2.add_component(goLeftRoom2Component);

    GameObject goTopRoom2("goTopRoom2", 450, 0);
    goTopRoom2.xF = 0; goTopRoom2.yF = 0;
    goTopRoom2.w = 70; goTopRoom2.h = 100;
    ChangeRoom goTopRoom2Component(goTopRoom2, room3.name(), ChangeRoom::Direction::Top);
    goTopRoom2.add_component(goTopRoom2Component);

    GameObject goBottonRoom3("goBottonRoom3", 450, 650);
    goBottonRoom3.xF = 0; goBottonRoom3.yF = 0;
    goBottonRoom3.w = 100; goBottonRoom3.h = 100;
    ChangeRoom goBottonRoom3Component(goBottonRoom3, room2.name(), ChangeRoom::Direction::Botton);
    goBottonRoom3.add_component(goBottonRoom3Component);

    GameObject goLeftRoom3("goLeftRoom3", 0, 320);
    goLeftRoom3.xF = 0; goLeftRoom3.yF = 0;
    goLeftRoom3.w = 70; goLeftRoom3.h = 100;
    ChangeRoom goLeftRoom3Component(goLeftRoom3, room4.name(), ChangeRoom::Direction::Left);
    goLeftRoom3.add_component(goLeftRoom3Component);

    GameObject goRightRoom4("goRightRoom4", 925, 320);
    goRightRoom4.xF = 0; goRightRoom4.yF = 0;
    goRightRoom4.w = 70; goRightRoom4.h = 100;
    ChangeRoom goRightRoom4Component(goRightRoom4, room3.name(), ChangeRoom::Direction::Right);
    goRightRoom4.add_component(goRightRoom4Component);

    GameObject goLeftRoom4("goLeftRoom4", 0, 300);
    goLeftRoom4.xF = 0; goLeftRoom4.yF = 0;
    goLeftRoom4.w = 70; goLeftRoom4.h = 100;
    ChangeRoom goLeftRoom4Component(goLeftRoom4, room5.name(), ChangeRoom::Direction::Left);
    goLeftRoom4.add_component(goLeftRoom4Component);

    GameObject goRightRoom5("goRightRoom5", 925, 320);
    goRightRoom5.xF = 0; goRightRoom5.yF = 0;
    goRightRoom5.w = 70; goRightRoom5.h = 100;
    ChangeRoom goRightRoom5Component(goRightRoom5, room4.name(), ChangeRoom::Direction::Right);
    goRightRoom5.add_component(goRightRoom5Component);

    //add to scene
    room1.add_game_object(spellQBanjo);
    room1.add_game_object(spellQGuitar);
    room1.add_game_object(spellQAccordion);
    room1.add_game_object(accordion);
    room1.add_game_object(eletric_guitar);
    room1.add_game_object(banjo);
    room1.add_game_object(player);
    room1.add_game_object(ghost);
    room1.add_game_object(goRightRoom1);

    room2.add_game_object(spellQBanjo);
    room2.add_game_object(spellQGuitar);
    room2.add_game_object(spellQAccordion);
    room2.add_game_object(accordion);
    room2.add_game_object(eletric_guitar);
    room2.add_game_object(banjo);
    room2.add_game_object(player);
    room2.add_game_object(ghost2);
    room2.add_game_object(goLeftRoom2);
    room2.add_game_object(goTopRoom2);

    room3.add_game_object(spellQBanjo);
    room3.add_game_object(spellQGuitar);
    room3.add_game_object(spellQAccordion);
    room3.add_game_object(accordion);
    room3.add_game_object(eletric_guitar);
    room3.add_game_object(banjo);
    room3.add_game_object(player);
    room3.add_game_object(goBottonRoom3);
    room3.add_game_object(goLeftRoom3);
    room3.add_game_object(ghost3);

    room4.add_game_object(spellQBanjo);
    room4.add_game_object(spellQGuitar);
    room4.add_game_object(spellQAccordion);
    room4.add_game_object(accordion);
    room4.add_game_object(eletric_guitar);
    room4.add_game_object(banjo);
    room4.add_game_object(player);
    room4.add_game_object(goRightRoom4);
    room4.add_game_object(goLeftRoom4);
    room4.add_game_object(ghost41);
    room4.add_game_object(ghost42);
    room4.add_game_object(ghost43);
    room4.add_game_object(ghost44);

    room5.add_game_object(spellQBanjo);
    room5.add_game_object(spellQGuitar);
    room5.add_game_object(spellQAccordion);
    room5.add_game_object(accordion);
    room5.add_game_object(eletric_guitar);
    room5.add_game_object(banjo);
    room5.add_game_object(player);
    room5.add_game_object(goRightRoom5);
    room5.add_game_object(ghost51);
    room5.add_game_object(ghost52);
    room5.add_game_object(ghost53);
    room5.add_game_object(ghost54);


    room1.add_game_object(nFragments);
    room2.add_game_object(nFragments);
    room3.add_game_object(nFragments);
    room4.add_game_object(nFragments);
    room5.add_game_object(nFragments);

    //Fragmento sala 1

    GameObject fragmento("fragmento",16*32,12*32);
    fragmento.xF = 0; fragmento.yF = 0;
    FragmentComponent obtainFrag(fragmento,1);
    ImageComponent guitarFrag(fragmento, "guitar.png", 1, 3);
    fragmento.add_component(obtainFrag);
    fragmento.add_component(guitarFrag);
    room1.add_game_object(fragmento);

    //Fragmentos sala 2

    GameObject fragmento2("fragmento",3*32,18*32);
    fragmento2.xF = 0; fragmento2.yF = 0;
    FragmentComponent obtainFrag2(fragmento2,1);
    ImageComponent guitarFrag2(fragmento2, "guitar.png", 1, 3);
    fragmento2.add_component(obtainFrag2);
    fragmento2.add_component(guitarFrag2);
    room2.add_game_object(fragmento2);

    //Fragmento sala 3

    GameObject fragmento3("fragmento",20*32,6*32);
    fragmento3.xF = 0; fragmento3.yF = 0;
    FragmentComponent obtainFrag3(fragmento3,1);
    ImageComponent guitarFrag3(fragmento3, "guitar.png", 1, 3);
    fragmento3.add_component(obtainFrag3);
    fragmento3.add_component(guitarFrag3);
    room3.add_game_object(fragmento3);

    //Fragmento 4
    GameObject fragmento4("fragmento",7*32,10*32);
    fragmento4.xF = 0; fragmento4.yF = 0;
    FragmentComponent obtainFrag4(fragmento4,1);
    ImageComponent guitarFrag4(fragmento4, "guitar.png", 1, 3);
    fragmento4.add_component(obtainFrag4);
    fragmento4.add_component(guitarFrag4);
    room5.add_game_object(fragmento4);

    GameObject menuBackground("menu_background", 0, 0);
    menuBackground.xF = 0; menuBackground.yF = 0;
    ImageComponent backgroundImage(menuBackground, "menu_background.png", 1, 1);
    menuBackground.add_component(backgroundImage);
    menu.add_game_object(menuBackground);

    GameObject playButton("playbutton", 50, 150);
    playButton.xF = 0; playButton.yF = 0;
    ImageComponent playImage(playButton,"play_button.png", 1, 1);
    playButton.add_component(playImage);
    menu.add_game_object(playButton);

    GameObject optionsButton("optionsbutton", 150, 300);
    optionsButton.xF = 0; optionsButton.yF = 0;
    ImageComponent optionsImage(optionsButton,"options_button.png", 1, 1);
    optionsButton.add_component(optionsImage);
    menu.add_game_object(optionsButton);

    GameObject quitButton("quitbutton", 250, 450);
    quitButton.xF = 0; quitButton.yF = 0;
    ImageComponent quitImage(quitButton,"quit_button.png", 1, 1);
    quitButton.add_component(quitImage);
    menu.add_game_object(quitButton);

    /*GameObject playbutton("playbutton",(globals::window_size.first/2)-50,(globals::window_size.second/2)-50);
    ImageComponent playImage(playbutton,"playbutton.png",1,1);
    playbutton.xF = 0; playbutton.yF = 0;
    playbutton.add_component(playImage);
    menu.add_game_object(playbutton);*/

    GameObject gameover("gameover",(globals::window_size.first/2)-100,(globals::window_size.second/2)-100);
    ImageComponent gameoverImage(gameover,"gameover.png",1,1);
    gameover.xF = 0; gameover.yF = 0;
    gameover.add_component(gameoverImage);
    GameoverScene.add_game_object(gameover);

    GameObject victory("victory",(globals::window_size.first/2)-100,(globals::window_size.second/2)-100);
    ImageComponent victoryImage(victory,"victory.png",1,1);
    victory.xF = 0; victory.yF = 0;
    victory.add_component(victoryImage);
    VictoryScene.add_game_object(victory);

    TileMap tilemap("assets/mapa1.txt", "mapa", 0, 0);
    TileSet tileset(32, 32, tilemap, "tilesheet.png", 1, 1);
    tilemap.setTileSet(tileset);
    tilemap.add_component(tileset);

    TileMap tilemap2("assets/mapa2.txt", "mapa", 0, 0);
    TileSet tileset2(32, 32, tilemap2, "tilesheet.png", 1, 1);
    tilemap2.setTileSet(tileset2);
    tilemap2.add_component(tileset2);

    TileMap tilemap3("assets/mapa3.txt", "mapa", 0, 0);
    TileSet tileset3(32, 32, tilemap3, "tilesheet.png", 1, 1);
    tilemap3.setTileSet(tileset3);
    tilemap3.add_component(tileset3);

    TileMap tilemap4("assets/mapa4.txt", "mapa", 0, 0);
    TileSet tileset4(32, 32, tilemap4, "tilesheet.png", 1, 1);
    tilemap4.setTileSet(tileset4);
    tilemap4.add_component(tileset4);

    TileMap tilemap5("assets/mapa5.txt", "mapa", 0, 0);
    TileSet tileset5(32, 32, tilemap5, "tilesheet.png", 1, 1);
    tilemap5.setTileSet(tileset5);
    tilemap5.add_component(tileset5);


    HUDLife hudlife("hudlife", 0, 0, &player);
    hudlife.xF = 0; hudlife.yF = 0;
    ImageComponent lifeBar(hudlife, "hud_life.png", 1, 1);
    CustomImageComponent lifeBarContent(hudlife, "hud_life_full.png", 1, 1);
    hudlife.setLifeBar(&lifeBar);
    hudlife.setLifeBarContent(&lifeBarContent);
    hudlife.add_component(lifeBar);
    hudlife.add_component(lifeBarContent);

    AudioComponent music(tilemap,"fase.mp3",true, true);
    tilemap.add_component(music);
    tilemap2.add_component(music);
    tilemap3.add_component(music);
    tilemap4.add_component(music);
    tilemap5.add_component(music);

    room1.add_game_object(tilemap);
    room1.add_game_object(hudlife);
    room1.add_game_object(HUDInstrument);

    room2.add_game_object(hudlife);
    room2.add_game_object(HUDInstrument);
    room2.add_game_object(tilemap2);

    room3.add_game_object(hudlife);
    room3.add_game_object(HUDInstrument);
    room3.add_game_object(tilemap3);

    room4.add_game_object(hudlife);
    room4.add_game_object(HUDInstrument);
    room4.add_game_object(tilemap4);

    room5.add_game_object(hudlife);
    room5.add_game_object(HUDInstrument);
    room5.add_game_object(tilemap5);


    // Game loop
    Game::instance.run();
    return 0;
}
