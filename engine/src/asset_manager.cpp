#include "asset_manager.hpp"
#include "sdl2include.h"
#include "sdl_log.h"
#include "log.h"
#include "game.hpp"

using namespace engine;
bool AssetManager::shutdown()
 {
     INFO("Dealocate AssetManager");
 
     INFO("Dealocate images");
     for(auto id_image: m_images)
     {
         SDL_DestroyTexture(id_image.second->texture);
         delete id_image.second;
     }
     m_images.clear();
 
     return true;
 }
Image * AssetManager::load_image(std::string path, bool use_base)
{   
    if(use_base)
        path = m_base_path + "sprites/" + path;

    if (m_images.find(path) == m_images.end())
    {
        if (path == "")
        {
            WARN("Invalid path for image!");
            exit(1);
        }

        SDL_Surface * surface = IMG_Load(path.c_str());

        if (surface == NULL)
        {
            WARN("Could not load image from path " << path);
            exit(1);
        }

        SDL_Texture * texture = SDL_CreateTextureFromSurface(Game::instance.canvas(), surface);

        if (texture == NULL)
        {
            WARN("Could not create texture from image!");
            exit(1);
        }

        Image * img = new Image;
        img->texture = texture;
        img->w = surface->w;
        img->h = surface->h;

        m_images[path] = img;

        SDL_FreeSurface(surface);
    }

    return m_images[path];  
}

TTF_Font * AssetManager::load_font(std::string path, int size, bool use_base)
{
    if(use_base)
        path = m_base_path + "fonts/" + path;

    auto path_size = std::make_pair(path, size);

    if (m_fonts.find(path_size) == m_fonts.end())
    {
        INFO("Loading new font...");

        auto m_font = TTF_OpenFont(path.c_str(), size);

        if(m_font == NULL)
        {
            SDL_TTF_ERROR("Could not load font from path " << path);
            return NULL;
        }

        m_fonts[path_size] = m_font;
    }

    return m_fonts[path_size];
}

Mix_Music * AssetManager::load_music(std::string path, bool use_base)
{
    if(use_base)
        path = m_base_path + "sounds/" + path;

    if (m_musics.find(path) == m_musics.end())
    {
        Mix_Music * music = Mix_LoadMUS(path.c_str());
        if (music == NULL)
        {
            SDL_MIX_ERROR("Could not load music from path " << path);
            return NULL;
        }

        m_musics[path] = music;
    }

    return m_musics[path];
}

Mix_Chunk * AssetManager::load_sound(std::string path, bool use_base)
{
    if(use_base)
        path = m_base_path + "sounds/" + path;

    if (m_sounds.find(path) == m_sounds.end())
    {
        Mix_Chunk * sound = Mix_LoadWAV(path.c_str());
        if (sound == NULL)
        {
            SDL_MIX_ERROR("Could not load sound from path " << path);
            return NULL;
        }

        m_sounds[path] = sound;
    }

    return m_sounds[path];
}