#include "game.hpp"

#include "log.h"
#include "sdl_log.h"

using namespace engine;

Game Game::instance;

void Game::set_properties(std::string name, std::pair<int, int> window_size)
{
    m_name = name;
    m_window_size = window_size;
}

bool setup_sdl()
{
    INFO("Setup SDL");

    INFO("Init video and audio");
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        SDL_ERROR("SDL_Init");
        return false;
    }

    INFO("Init image png");
    int img_flags = IMG_INIT_PNG;
    if(!(IMG_Init(img_flags) & img_flags))
    {
        SDL_IMG_ERROR("IMG_Init");
        return false;
    }

    INFO("Init TTF");
    if(TTF_Init() == -1)
    {
        SDL_TTF_ERROR("TTF_Init");
        return false;
    }

    INFO("Open audio Mixer");
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        SDL_MIX_ERROR("Mix_OpenAudio");
        return false;
    }

    return true;
}

bool Game::create_window()
{
    INFO("Create Window (" << m_name << ", " << m_window_size.first << ", " <<
         m_window_size.second << ")");

    m_window = SDL_CreateWindow(
        m_name.c_str(),         // Title
        SDL_WINDOWPOS_CENTERED, // Position x. SDL_WINDOWPOS_UNDEFINED
        SDL_WINDOWPOS_CENTERED, // Position y. SDL_WINDOWPOS_UNDEFINED
        m_window_size.first,    // width
        m_window_size.second,   // height
        SDL_WINDOW_SHOWN        // Window flags, SDL_WindowFlags for more
    );

    if (m_window == NULL)
    {
        SDL_ERROR("SDL_CreateWindow");
        return false;
    }

    INFO("Create canvas");
    m_canvas = SDL_CreateRenderer(
        m_window,
        -1, // Render driver. -1 to the first one that support the flags
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (m_canvas == NULL)
    {
        SDL_ERROR("SDL_CreateRenderer");
        return false;
    }

    SDL_SetRenderDrawColor(m_canvas,
                           m_background_color.r, m_background_color.b,
                           m_background_color.g, m_background_color.a);

    return true;
}

bool teardown_sdl()
{
    INFO("Teardown SDL");

    INFO("Quit SDL Mix");
    Mix_Quit();

    INFO("Quit SDL TTF");
    TTF_Quit();

    INFO("Quit SDL IMG");
    IMG_Quit();

    INFO("Quit SDL");
    SDL_Quit();

    return true;
}

bool Game::destroy_window()
{
    INFO("Destroy canvas");
    SDL_DestroyRenderer(m_canvas);
    m_canvas = NULL;

    INFO("Destroy window");
    SDL_DestroyWindow(m_window);
    m_window = NULL;

    return true;
}
void Game::handleEvents()
{
    if(m_scene != NULL) m_scene->update();
}
void Game::run()
{
    INFO("Game " << m_name << "Setup");
    
    const int FPS = 60;
    const int DELAY_TIME = 1000.0f / FPS;
    Uint32 frameStart, frameTime;

    m_state = State::init;

    if (setup_sdl() && create_window())
    {
        INFO("Start game loop");
        m_state = State::main_loop;

        if (m_scene == NULL)
        {
            WARN("No scenes to run!");
            m_state = State::exit_loop;
        }
        else m_state = State::main_loop_change_scene;

        while(m_state != State::exit_loop)
        {
            if(handle_scene_changes() == false) break;
            frameStart = SDL_GetTicks();

            SDL_Event evt;
            while(SDL_PollEvent(&evt) != 0)
            {
                if (evt.type == SDL_QUIT) m_state = State::exit_loop;
            }
            
            SDL_RenderClear(m_canvas);

            m_scene->draw();

            handleEvents();
            
            SDL_RenderPresent(m_canvas);
            frameTime = SDL_GetTicks() - frameStart;
            
            if(frameTime< DELAY_TIME)
            {
                SDL_Delay((int)(DELAY_TIME - frameTime));
            }
            
        }

        INFO("Cleaning up resources...");
        if(m_scene) m_scene->shutdown();
    }

    INFO("Game Shutdown");
    m_state = State::shutdown;
    destroy_window();
    teardown_sdl();
}

void Game::set_background_color(int r, int g, int b, int a)
{
    m_background_color.r = r;
    m_background_color.g = g;
    m_background_color.b = b;
    m_background_color.a = a;

    if (m_canvas != NULL)
    {
        SDL_SetRenderDrawColor(m_canvas,
                               m_background_color.r, m_background_color.b,
                               m_background_color.g, m_background_color.a);
    }
}

bool Game::add_scene(Scene & scene)
{
    auto id = scene.name();
    INFO("Add scene " << id);

    if (m_scenes.find(id) != m_scenes.end())
    {
        WARN("Scene " << id << " already exists!");
        return false;
    }

    m_scenes[id] = &scene;

    if (m_scene == NULL) change_scene(id);

    return true;
}

bool Game::change_scene(const std::string & id)
{
    INFO("Change scene to " << id);

    if (m_scenes.find(id) == m_scenes.end())
    {
        WARN("Scene " << id << " not found!");
        return false;
    }

    m_last_scene = m_scene;
    m_scene = m_scenes[id];
    m_state = State::main_loop_change_scene;
    return true;
}

bool Game::handle_scene_changes()
{
    if (m_state == State::main_loop_change_scene)
    {
        INFO("Tchau ");
        if (m_scene == NULL)
        {
            WARN("No scenes to run!");
            return false;
        }
        else
        {
            INFO("Scenes changing from " <<
                 (m_last_scene ? m_last_scene->name() : "NULL") << " to " <<
                 m_scene->name() << "...");
            if(m_last_scene) {
                m_last_scene->shutdown();
                m_last_scene->asset_manager().shutdown();
            }
            m_scene->init();

            m_state = State::main_loop;
        }
    }

    return true;
}
