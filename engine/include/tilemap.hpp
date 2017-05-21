#ifndef __ENGINE_TILEMAP__
#define __ENGINE_TILEMAP__

#include <string>
#include <vector>
#include "components/image.hpp"
#include "tileset.hpp"
#include "vector.hpp"

namespace engine {

class TileMap : public GameObject {
public:

    TileMap(std::string image_path, std::string map_path, int width, int height, std::string game_object_name,int _x,int _y):
    GameObject(game_object_name,_x,_y), m_image_path(image_path), m_map_path(map_path),m_width(width),m_height(height){}
        
    virtual ~TileMap(){}

    bool init();
    void setTileSet(TileSet *tileset);
    int& at(int x, int y, int z);
    void renderLayer(int layer, int camera_x = 0, int camera_y = 0);
    bool draw();
    

private:
    std::vector<int> tile_matrix;
    int m_width, m_height;
    int map_depth;
    int map_height;
    int map_width;
    TileSet *m_tileset;
    std::string m_map_path;
    std::string m_image_path;
};

}

#endif
