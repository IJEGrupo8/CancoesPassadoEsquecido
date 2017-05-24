#ifndef __ENGINE_GAME__
#define __ENGINE_GAME__

#include <string>
#include <unordered_map>
#include <utility>

#include "scene.hpp"
#include "sdl2include.h"

namespace engine {

static const std::string DEFAULT_GAME_NAME = "Game";
static const std::pair<int, int> DEFAULT_WINDOW_SIZE(100, 100);

class Game {
public:
    enum class State {
        created,
        init,
        main_loop,
        main_loop_change_scene,
        exit_loop,
        paused,
        shutdown
    };

    static Game instance;

    void set_properties(std::string new_name, std::pair<int, int> window_size);

    void run();
    void set_background_color(int r, int g, int b, int a);

    bool add_scene(Scene & scene);
    bool change_scene(const std::string & id);

    inline SDL_Renderer * canvas() { return m_canvas; }
    inline AssetManager & asset_manager() { return m_scene->asset_manager(); }
    Scene * m_scene;       // Current Scene

private:
    Game()
        : m_scene(NULL), m_name(DEFAULT_GAME_NAME), m_window_size(DEFAULT_WINDOW_SIZE),
          m_state(State::created), m_window(NULL), m_canvas(NULL),
          m_background_color({0xff, 0xff, 0xff, 0xff}),
          m_last_scene(NULL) {}

    std::string         m_name;
    std::pair<int, int> m_window_size;
    State               m_state;
    std::string         m_scene_intent;

    SDL_Window   * m_window;
    SDL_Renderer * m_canvas;
    SDL_Color      m_background_color;

    std::unordered_map<std::string, Scene *> m_scenes;
    Scene * m_last_scene;  // Last Scene Played

    bool create_window();
    bool destroy_window();
    void handleEvents();

    bool handle_scene_changes();
};

}

#endif
