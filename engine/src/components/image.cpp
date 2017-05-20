#include "components/image.hpp"

#include "game.hpp"
#include "log.h"
#include "sdl_log.h"

using namespace engine;

bool ImageComponent::init()
{
    INFO("Init ImageComponent");

    if (m_path == "")
    {
        WARN("Invalid path for image!");
        return false;
    }

    SDL_Surface * image = IMG_Load(m_path.c_str());

    if (image == NULL)
    {
        SDL_IMG_ERROR("Could not load image from path " << m_path);
        return false;
    }

    m_texture = SDL_CreateTextureFromSurface(Game::instance.canvas(), image);
    INFO("INIT TEXTURE ="<<m_texture);
    if (m_texture == NULL)
    {
        SDL_ERROR("Could not create texture from image!");
        return false;
    }

    m_game_object->set_size(image->w/i, image->h/j);

    SDL_FreeSurface(image);
    return true;
}

bool ImageComponent::shutdown()
{
    INFO("Shutdown ImageComponent");

    SDL_DestroyTexture(m_texture);
    m_texture = NULL;

    return true;
}

void ImageComponent::draw()
{
    SDL_Rect renderQuad = {
        (int) m_game_object->physics.position.getX(),
        (int) m_game_object->physics.position.getY(),
        m_game_object->w,
        m_game_object->h
    };
    SDL_Rect frameQuad = {
        m_game_object->xF,
        m_game_object->yF,
        m_game_object->w,
        m_game_object->h
    };
    //INFO(""<< m_texture);

    //INFO("draw "<< (m_game_object->xF)%i << "  "<< m_game_object->yF);
    //SDL_RenderCopy(Game::instance.canvas(), m_texture, &frameQuad, &renderQuad);
    SDL_RenderCopyEx(Game::instance.canvas(), m_texture, &frameQuad, &renderQuad, 0, 0, SDL_FLIP_NONE);
    //INFO("ERROR " << SDL_GetError());

}

