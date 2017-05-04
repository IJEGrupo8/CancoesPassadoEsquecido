#include "game.hpp"
#include "gameobject.hpp"
#include "scene.hpp"
#include "components/image.hpp"
#include "components/text.hpp"
#include "components/audio.hpp"
#include "player.hpp"
#include "gamescene.hpp"
#include "menuscene.hpp"


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
    //ImageComponent playerImage(player, "assets/sprites/girl.png",4,4);
        
    //player.add_component(playerImage);

    Instrument banjo("Banjo", 100,100);
    Instrument eletric_guitar("Eletric Guitar", 100,100);
    Instrument accordion("Accordion", 100,100);

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

    gameplay.add_game_object(player);

    // Game loop
    Game::instance.run();
    return 0;
}
