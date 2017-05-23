#include "asset_manager.hpp"
#include "sdl2include.h"
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