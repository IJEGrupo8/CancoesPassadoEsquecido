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
#include "components/talknpc.hpp"
#include "basicspell.hpp"
#include "customimagecomponent.hpp"
#include "player.hpp"
#include "gamescene.hpp"
#include "menuscene.hpp"
#include "gameover.hpp"
#include "spell.hpp"
#include "stopspell.hpp"
#include "slowspell.hpp"
#include "tilemap.hpp"
#include "tileset.hpp"
#include "log.h"
#include "gameglobals.hpp"
#include "hudlife.hpp"
#include "hudbox.hpp"
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
    GameOverScene GameoverScene("Gameover");
    GameOverScene VictoryScene("Victory");

    GameScene gameplay("stage_1");

    gameplay.add_room("stage_1_room_1");
    gameplay.add_room("stage_1_room_2");
    gameplay.add_room("stage_1_room_3");
    gameplay.add_room("stage_1_room_4");
    gameplay.add_room("stage_1_room_5");

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

    gameplay.add_game_object_to_room("stage_1_room_1", tilemap);
    gameplay.add_game_object_to_room("stage_1_room_2", tilemap2);
    gameplay.add_game_object_to_room("stage_1_room_3", tilemap3);
    gameplay.add_game_object_to_room("stage_1_room_4", tilemap4);
    gameplay.add_game_object_to_room("stage_1_room_5", tilemap5);

    /* Gamescene*/
    Game::instance.add_scene(menu);
    Game::instance.add_scene(gameplay);
    Game::instance.add_scene(GameoverScene);
    Game::instance.add_scene(VictoryScene);
 
    Player player(globals::player, 3*32, 3*32);
    player.xF = 0; player.yF = 0;

    //Declaring instruments
    Instrument banjo(globals::banjo, 3*32, 3*32);
    //Declaring spells
    BasicSpell spellQBanjo("spellQBanjo",&player,0,0,1500,6000);
    spellQBanjo.xF = 0; spellQBanjo.yF = 0;

    StopSpell spellWBanjo("spellWBanjo",&player,0,0,1500,6000);
    spellWBanjo.xF = 0; spellWBanjo.yF = 0;

    SlowSpell spellEBanjo("spellEBanjo",&player,0,0,1500,4000);
    spellEBanjo.xF = 0; spellEBanjo.yF = 0;

    AudioComponent somWBanjo(spellWBanjo,"drumsBasic.wav",false,false);
    AudioComponent somEBanjo(spellEBanjo,"drumsBasic.wav",false,false);
    AudioComponent somQBanjo(spellQBanjo,"drumsBasic.wav",false,false);

    ImageComponent banjoEImage(spellEBanjo, "musicnote.png", 3, 3);
    ImageComponent banjoWImage(spellWBanjo, "musicnote.png", 3, 3);
    ImageComponent banjoQImage(spellQBanjo, "musicnote.png", 3, 3);

    spellEBanjo.add_component(banjoEImage);
    spellEBanjo.add_component(somEBanjo);

    spellQBanjo.add_component(banjoQImage);
    spellQBanjo.add_component(somQBanjo);

    spellWBanjo.add_component(banjoWImage);
    spellWBanjo.add_component(somWBanjo);

    //Adicionando spell ao instrumento
    banjo.addSpell(globals::spellQ,&spellQBanjo);
    banjo.addSpell(globals::spellW,&spellWBanjo);
    banjo.addSpell(globals::spellE,&spellEBanjo);

    player.addInstrument(globals::banjo, banjo);
 
    HUDInstrument HUDInstrument("hudinstrument", globals::window_size.first-250, globals::window_size.second-10, &player);
    HUDInstrument.xF = 0; HUDInstrument.yF = 0;
    TextComponent banjoActiveHUD(HUDInstrument,"COOLDOWN Q","font.ttf",20, {255,255,255});
    TextComponent eletricGuitarActiveHUD(HUDInstrument, "COOLDOWN W","font.ttf",20, {255,255,255});
    TextComponent accordionActiveHUD(HUDInstrument, "COOLDOWN E","font.ttf",20, {255,255,255});

    HUDInstrument.addHUD(globals::spellQ, &banjoActiveHUD);
    HUDInstrument.addHUD(globals::spellW, &eletricGuitarActiveHUD);
    HUDInstrument.addHUD(globals::spellE, &accordionActiveHUD);

    HUDInstrument.add_component(banjoActiveHUD);
    HUDInstrument.add_component(eletricGuitarActiveHUD);
    HUDInstrument.add_component(accordionActiveHUD);

    //Animation
    AnimationControllerComponent banjoController(player);

    AnimationComponent banjoMoveLeft(player,"walk.png",8,4,1000,0,7,-1);
    AnimationComponent banjoMoveRight(player,"walk.png",8,4,1000,8,15,-1);
    AnimationComponent banjoMoveDown(player,"walk.png",8,4,2000,16,19,-1);
    AnimationComponent banjoMoveUp(player,"walk.png",8,4,2000,24,27,-1);

    banjoController.addAnimation(globals::moveLeft,banjoMoveLeft);
    banjoController.addAnimation(globals::moveRight,banjoMoveRight);
    banjoController.addAnimation(globals::moveDown,banjoMoveDown);
    banjoController.addAnimation(globals::moveUp,banjoMoveUp);

    player.add_component(banjoController);
    player.addSprite(globals::banjo, &banjoController);

    MoveDirectionals move(player);
    player.add_component(move);

    GameObject nFragments("nFragments",10,40);
    TextComponent fragmentText(nFragments,"Numero de fragmentos: ", "font.ttf",20, {255,255,255});
    nFragments.add_component(fragmentText);
    player.nFragments = &fragmentText;

    gameplay.get_room("stage_1_room_1")->add_enemy("ghost", 25*32, 6*32, &player, 100, globals::SAD_ENEMY);
    //gameplay.get_room("stage_1_room_1")->add_enemy("ghost12", 21*32, 6*32, &player, 100);
    //gameplay.get_room("stage_1_room_1")->add_enemy("ghost13", 22*32, 6*32, &player, 100);
    //gameplay.get_room("stage_1_room_1")->add_enemy("ghost14", 24*32, 6*32, &player, 100);
    //gameplay.get_room("stage_1_room_1")->add_enemy("ghost15", 23*32, 6*32, &player, 100);
    //gameplay.get_room("stage_1_room_1")->add_enemy("ghost16", 25*32, 6*32, &player, 100);
    //gameplay.get_room("stage_1_room_1")->add_enemy("ghost17", 26*32, 6*32, &player, 100);
    //gameplay.get_room("stage_1_room_1")->add_enemy("ghost18", 27*32, 6*32, &player, 100);
    //gameplay.get_room("stage_1_room_1")->add_enemy("ghost19", 28*32, 6*32, &player, 100);


    gameplay.get_room("stage_1_room_2")->add_enemy("ghost2", 25*32, 6*32, &player, 100, globals::MAD_ENEMY);
    gameplay.get_room("stage_1_room_3")->add_enemy("ghost3", 100, 100, &player, 100, globals::MAD_ENEMY);
    //gameplay.get_room("stage_1_room_4")->add_enemy("ghost41", 3*32, 3*32, &player, 100, globals::MAD_ENEMY);
    //gameplay.get_room("stage_1_room_4")->add_enemy("ghost42", 28*32, 3*32, &player, 100, globals::MAD_ENEMY);
    //gameplay.get_room("stage_1_room_4")->add_enemy("ghost43", 3*32, 19*32, &player, 100, globals::MAD_ENEMY);
    //gameplay.get_room("stage_1_room_4")->add_enemy("ghost44", 28*32, 15*32, &player, 100, globals::MAD_ENEMY);
    gameplay.get_room("stage_1_room_5")->add_enemy("ghost51", 3*32, 3*32, &player, 100, globals::MAD_ENEMY);
    gameplay.get_room("stage_1_room_5")->add_enemy("ghost52", 28*32, 3*32, &player, 100, globals::MAD_ENEMY);
    gameplay.get_room("stage_1_room_5")->add_enemy("ghost53", 3*32, 19*32, &player, 100, globals::MAD_ENEMY);
    gameplay.get_room("stage_1_room_5")->add_enemy("ghost54", 28*32, 15*32, &player, 100, globals::MAD_ENEMY);

    //change room handler
/*    GameObject goRightRoom1("goRightRoom1", 925,200);
    goRightRoom1.xF = 0; goRightRoom1.yF = 0;
    ChangeRoom goRightRoom1Component(goRightRoom1,"stage_1_room_2",ChangeRoom::Direction::Right);
    goRightRoom1.add_component(goRightRoom1Component);
    goRightRoom1.w = 100; goRightRoom1.h = 100;*/

    gameplay.get_room("stage_1_room_1")->add_room_transition("goRightRoom1", 925,200,100,100,"stage_1_room_2",ChangeRoom::Direction::Right);
    gameplay.get_room("stage_1_room_2")->add_room_transition("goLeftRoom2", 0, 320,100,100,"stage_1_room_1",ChangeRoom::Direction::Left);
    gameplay.get_room("stage_1_room_2")->add_room_transition("goTopRoom2", 450, 0,70,100,"stage_1_room_3",ChangeRoom::Direction::Top);
    gameplay.get_room("stage_1_room_3")->add_room_transition("goBottonRoom3", 450, 650,100,100,"stage_1_room_2",ChangeRoom::Direction::Botton);
    gameplay.get_room("stage_1_room_3")->add_room_transition("goLeftRoom3",0, 320,70,100,"stage_1_room_4",ChangeRoom::Direction::Left);
    gameplay.get_room("stage_1_room_4")->add_room_transition("goRightRoom4",925, 320,70,100,"stage_1_room_3",ChangeRoom::Direction::Right);
    gameplay.get_room("stage_1_room_4")->add_room_transition("goLeftRoom4", 0, 300,70,100,"stage_1_room_5",ChangeRoom::Direction::Left);
    gameplay.get_room("stage_1_room_5")->add_room_transition("goRightRoom5", 0, 925, 320,100,"stage_1_room_4",ChangeRoom::Direction::Right);

    gameplay.add_game_object(spellQBanjo);
    gameplay.add_game_object(spellWBanjo);
    gameplay.add_game_object(spellEBanjo);
    gameplay.add_game_object(banjo);
    gameplay.add_game_object(player);
    gameplay.add_game_object(nFragments);

    //Fragmento sala 1

    GameObject fragmento("fragmento",16*32,12*32);
    fragmento.xF = 0; fragmento.yF = 0;
    FragmentComponent obtainFrag(fragmento,1);
    ImageComponent guitarFrag(fragmento, "guitar.png", 1, 3);
    fragmento.add_component(obtainFrag);
    fragmento.add_component(guitarFrag);
    gameplay.add_game_object_to_room("stage_1_room_1",fragmento);

    //Fragmentos sala 2

    GameObject fragmento2("fragmento",3*32,18*32);
    fragmento2.xF = 0; fragmento2.yF = 0;
    FragmentComponent obtainFrag2(fragmento2,1);
    ImageComponent guitarFrag2(fragmento2, "guitar.png", 1, 3);
    fragmento2.add_component(obtainFrag2);
    fragmento2.add_component(guitarFrag2);
    gameplay.add_game_object_to_room("stage_1_room_2",fragmento2);

    //Fragmento sala 3

    GameObject fragmento3("fragmento",20*32,6*32);
    fragmento3.xF = 0; fragmento3.yF = 0;
    FragmentComponent obtainFrag3(fragmento3,1);
    ImageComponent guitarFrag3(fragmento3, "guitar.png", 1, 3);
    fragmento3.add_component(obtainFrag3);
    fragmento3.add_component(guitarFrag3);
    gameplay.add_game_object_to_room("stage_1_room_3",fragmento3);

    //Fragmento 4
    GameObject fragmento4("fragmento",7*32,10*32);
    fragmento4.xF = 0; fragmento4.yF = 0;
    FragmentComponent obtainFrag4(fragmento4,1);
    ImageComponent guitarFrag4(fragmento4, "guitar.png", 1, 3);
    fragmento4.add_component(obtainFrag4);
    fragmento4.add_component(guitarFrag4);
    gameplay.add_game_object_to_room("stage_1_room_5",fragmento4);

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


    HUDLife hudlife("hudlife", 0, 0, &player);
    hudlife.xF = 0; hudlife.yF = 0;
    ImageComponent lifeBar(hudlife, "hud_life.png", 1, 1);
    CustomImageComponent lifeBarContent(hudlife, "hud_life_full.png", 1, 1);
    hudlife.setLifeBar(&lifeBar);
    hudlife.setLifeBarContent(&lifeBarContent);
    hudlife.add_component(lifeBar);
    hudlife.add_component(lifeBarContent);

    GameObject npcjoao("npcjoao", 500, 500);
    npcjoao.xF = 0; npcjoao.yF = 0;    
    ImageComponent joaoImage(npcjoao, "boy.png",4,4);
    npcjoao.add_component(joaoImage);
    

    HUDBox npcBox("npc_box",212, 600);
    npcBox.xF = 0;
    npcBox.yF = 0;
    TextComponent joaoline(npcBox,".             Oiiir, eu sou o joao!","font.ttf",20, {255,255,255});
    ImageComponent boxImage(npcBox, "dialog_box.png",1,1);
    npcBox.add_component(boxImage);
    npcBox.add_component(joaoline);
    
    TalkNpc talkjoao(npcjoao,&npcBox);
    npcjoao.add_component(talkjoao);

    gameplay.add_game_object_to_room("stage_1_room_1", npcjoao);
    gameplay.add_game_object_to_room("stage_1_room_1", npcBox);
    

    AudioComponent music(tilemap,"fase.wav",true, true);
    tilemap.add_component(music);
    tilemap2.add_component(music);
    tilemap3.add_component(music);
    tilemap4.add_component(music);
    tilemap5.add_component(music);


    gameplay.add_game_object(hudlife);
    gameplay.add_game_object(HUDInstrument);


    // Game loop
    Game::instance.run();
    return 0;
}
