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
    GameScene room1("stage_1_room_1");
    GameScene room2("stage_1_room_2");
    GameScene room3("stage_1_room_3");
    GameScene room4("stage_1_room_4");
    
    /* Gamescene*/
    Game::instance.add_scene(menu);
    Game::instance.add_scene(room1);
    Game::instance.add_scene(room2);
    Game::instance.add_scene(room3);
    Game::instance.add_scene(room4);
    Game::instance.add_scene(GameoverScene);

    Player player(globals::player,100,100);
    player.xF = 0; player.yF = 0;

    MoveDirectionals move(player);

    //Declaring instruments
    Instrument banjo(globals::banjo, 100,100);
    Instrument eletric_guitar(globals::eletric_guitar, 100,100);
    Instrument accordion(globals::accordion, 100,100);
    //Declaring spells
    Spell spellQBanjo("spellQBanjo",&player,0,0,3000,3000);
    Spell spellWBanjo("spellWBanjo",&player,0,0,5000,5000);
    Spell spellEBanjo("spellEBanjo",&player,0,0,5000,1000);

    AudioComponent somQ(spellQBanjo,"pika.wav",false,false);
    AudioComponent somE(spellWBanjo,"pika.wav",false,false); 
    AudioComponent somW(spellEBanjo,"pika.wav",false,false);

    PushEnemy pushQ(spellQBanjo);

    spellQBanjo.xF = 0; spellQBanjo.yF = 0;
    spellWBanjo.xF = 0; spellWBanjo.yF = 0;
    spellEBanjo.xF = 0; spellEBanjo.yF = 0;

    //Adicionando imagem ao spell

    AnimationComponent explosionQImage(spellQBanjo, "explosion.png", 4, 4,1000,0,15);
    AnimationComponent explosionWImage(spellWBanjo, "explosion.png", 4, 4,500,0,15,4);
    AnimationComponent explosionEImage(spellEBanjo, "explosion.png", 4, 4,1000,0,15);

    //AnimationControllerComponent explosionController();

    spellQBanjo.add_component(explosionQImage);
    spellWBanjo.add_component(explosionWImage);
    spellEBanjo.add_component(explosionEImage); 

    spellQBanjo.add_component(somQ);
    spellWBanjo.add_component(somE);
    spellEBanjo.add_component(somW);
    
    spellQBanjo.add_component(pushQ);
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

    player.addSprite(globals::banjo, &banjoImage);
    player.addSprite(globals::eletric_guitar, &eletricGuitarImage);
    player.addSprite(globals::accordion, &accordionImage);

    player.add_component(banjoImage);
    player.add_component(eletricGuitarImage);
    player.add_component(accordionImage);

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

    //change room handler
    GameObject goRightRoom1("goRightRoom1", 925,220);
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
    goTopRoom2.w = 100; goTopRoom2.h = 100;
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

    //add to scene
    room1.add_game_object(spellWBanjo);
    room1.add_game_object(spellEBanjo);
    room1.add_game_object(spellQBanjo);
    room1.add_game_object(accordion);
    room1.add_game_object(eletric_guitar);
    room1.add_game_object(banjo);
    room1.add_game_object(player);
    room1.add_game_object(ghost);
    room1.add_game_object(goRightRoom1);

    room2.add_game_object(spellWBanjo);
    room2.add_game_object(spellEBanjo);
    room2.add_game_object(spellQBanjo);
    room2.add_game_object(accordion);
    room2.add_game_object(eletric_guitar);
    room2.add_game_object(banjo);
    room2.add_game_object(player);
    room2.add_game_object(ghost2);
    room2.add_game_object(goLeftRoom2);
    room2.add_game_object(goTopRoom2);

    room3.add_game_object(spellWBanjo);
    room3.add_game_object(spellEBanjo);
    room3.add_game_object(spellQBanjo);
    room3.add_game_object(accordion);
    room3.add_game_object(eletric_guitar);
    room3.add_game_object(banjo);
    room3.add_game_object(player);
    room3.add_game_object(goBottonRoom3);
    room3.add_game_object(goLeftRoom3);
    room3.add_game_object(ghost3);

    room4.add_game_object(spellWBanjo);
    room4.add_game_object(spellEBanjo);
    room4.add_game_object(spellQBanjo);
    room4.add_game_object(accordion);
    room4.add_game_object(eletric_guitar);
    room4.add_game_object(banjo);
    room4.add_game_object(player);
    room4.add_game_object(goRightRoom4);
    room4.add_game_object(ghost41);
    room4.add_game_object(ghost42);
    room4.add_game_object(ghost43);
    room4.add_game_object(ghost44);

    room1.add_game_object(nFragments);
    room2.add_game_object(nFragments);
    room3.add_game_object(nFragments);
    room4.add_game_object(nFragments);

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

    GameObject playbutton("playbutton",(globals::window_size.first/2)-50,(globals::window_size.second/2)-50);
    ImageComponent playImage(playbutton,"playbutton.png",1,1);
    playbutton.xF = 0; playbutton.yF = 0;
    playbutton.add_component(playImage);
    menu.add_game_object(playbutton);

    GameObject gameover("gameover",(globals::window_size.first/2)-100,(globals::window_size.second/2)-100);
    ImageComponent gameoverImage(gameover,"gameover.png",1,1);
    gameover.xF = 0; gameover.yF = 0;
    gameover.add_component(gameoverImage);
    GameoverScene.add_game_object(gameover);

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

    room1.add_game_object(tilemap); 
    //room2.add_game_object(tilemap);   
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

 
/*
    room1.add_game_object(tilemap);
    room2.add_game_object(tilemap);   
    room1.add_game_object(hudlife);
    room1.add_game_object(HUDInstrument);

    room2.add_game_object(hudlife);
    room2.add_game_object(HUDInstrument);
    room2.add_game_object(tilemap2);
 */   

    // Game loop
    Game::instance.run();
    return 0;
}
