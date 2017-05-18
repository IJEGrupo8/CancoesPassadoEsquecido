#ifndef __ENGINE_TILESET__
#define __ENGINE_TILESET__

#include <string>
#include "gameobject.hpp"
#include "components/image.hpp"

namespace engine {

class GameObject;

class TileSet : public ImageComponent{
public:

    TileSet(int width, int height, GameObject & game_object, std::string path,int m_i, int m_j);

    virtual ~TileSet();

    void render(int index, int x, int y);
    int getWidth();
    int getHeight();
    bool init();

private:
    int rows;
    int columns;
    int m_width;
    int m_height;
};

}

#endif
