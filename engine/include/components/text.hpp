#ifndef __ENGINE_COMPONENTS_TEXT__
#define __ENGINE_COMPONENTS_TEXT__

#include <string>
#include <utility>

#include "sdl2include.h"

#include "color.hpp"
#include "components/component.hpp"

namespace engine {

class TextComponent : public Component {
public:

    TextComponent(
        GameObject & game_object,
        std::string  text,
        std::string  font_path,
        int          font_size,
        Color        color=Color(),
        Color        background_color=Color(0x0, 0x0, 0x0, 0x00)
    )
        : Component(game_object), m_text(text), m_font_path(font_path),
          m_font_size(font_size), m_color(color),
          m_background_color(background_color), m_texture(NULL), m_font(NULL),
          m_w(0), m_h(0) {}

    ~TextComponent() {}

    bool init();
    bool shutdown();

    void draw();
    void setText(std::string _text){m_text = _text;}
    
    inline void enable_high_quality()  { m_high_quality = true; }
    inline void disable_high_quality() { m_high_quality = false; }

private:
    std::string m_text;
    std::string m_font_path;
    int         m_font_size;
    bool        m_high_quality;
    Color       m_color;
    Color       m_background_color;

    SDL_Texture * m_texture;
    TTF_Font    * m_font;

    int m_w;
    int m_h;
};

}

#endif

