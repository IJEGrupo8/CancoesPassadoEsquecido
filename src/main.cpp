#include "game.hpp"
#include "gameobject.hpp"
#include "scene.hpp"
#include "components/image.hpp"
#include "components/text.hpp"
#include "components/audio.hpp"
#include "components/animation.hpp"
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
    GameScene gameplay("Gameplay");
    /*MenuScene menu("Menu");
    
    Game::instance.add_scene(menu);
    
    GameObject playbutton("playbutton",200,200);
    ImageComponent playImage(playbutton,"assets/sprites/playbutton.png",1,1);
    playbutton.add_component(playImage);
    menu.add_game_object(playbutton);
*/

    /* Gamescene*/
    Game::instance.add_scene(gameplay);

    Player player("Player1",100,100);
    player.xF = 0; player.yF = 0;

    //Declaring instruments
    Instrument banjo("Banjo", 100,100);
    Instrument eletric_guitar("Eletric Guitar", 100,100);
    Instrument accordion("Accordion", 100,100);
    //Declaring spells
    Spell spellQBanjo("spellQBanjo",&player,0,0);
    Spell spellWBanjo("spellWBanjo",&player,0,0);
    Spell spellEBanjo("spellEBanjo",&player,0,0);

    spellQBanjo.xF = 0; spellQBanjo.yF = 0;
    spellWBanjo.xF = 0; spellWBanjo.yF = 0;
    spellEBanjo.xF = 0; spellEBanjo.yF = 0;

    //Adicionando imagem ao spell

    AnimationComponent explosionQImage(spellQBanjo, "assets/sprites/explosion.png", 4, 4);
    AnimationComponent explosionWImage(spellWBanjo, "assets/sprites/explosion.png", 4, 4);
    AnimationComponent explosionEImage(spellEBanjo, "assets/sprites/explosion.png", 4, 4);

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

    ImageComponent banjoImage(player, "assets/sprites/girl2.png", 4, 4);
    ImageComponent eletricGuitarImage(player, "assets/sprites/girl3.png", 4, 4);
    ImageComponent accordionImage(player, "assets/sprites/girl4.png", 4, 4);

    player.addSprite(globals::banjo, &banjoImage);
    player.addSprite(globals::eletric_guitar, &eletricGuitarImage);
    player.addSprite(globals::accordion, &accordionImage);

    player.add_component(banjoImage);
    player.add_component(eletricGuitarImage);
    player.add_component(accordionImage);

    gameplay.add_game_object(spellWBanjo);
    gameplay.add_game_object(spellEBanjo);
    gameplay.add_game_object(spellQBanjo);
    gameplay.add_game_object(accordion);
    gameplay.add_game_object(eletric_guitar);
    gameplay.add_game_object(banjo);
    gameplay.add_game_object(player);

    // Game loop
    Game::instance.run();
    return 0;
}
