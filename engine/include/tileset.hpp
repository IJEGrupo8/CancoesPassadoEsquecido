#ifndef __ENGINE_TILESET__
#define __ENGINE_TILESET__

#include <string>
#include "gameobject.hpp"
#include "components/image.hpp"

namespace engine {

class GameObject;

class TileSet : public ImageComponent{
public:

    TileSet(int width, int height, GameObject & game_object, std::string path,int m_i, int m_j):
    ImageComponent(game_object, path,m_i,m_j), m_width(width), m_height(height){}

    virtual ~TileSet(){}

    void render(int index, int x, int y);
    int getWidth();
    int getHeight();
    bool init();

private:
    int m_rows;
    int m_columns;
    int m_width;
    int m_height;
};

}

#endif
