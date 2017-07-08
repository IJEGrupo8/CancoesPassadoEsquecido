#ifndef __IMAGE_SCENE__
#define __IMAGE_SCENE__

#include <string>
#include "scene.hpp"

using namespace engine;

class ImageScene : public Scene{
public:

    ImageScene() : Scene("") {}
    ImageScene(std::string _name)
        : Scene(_name) {}

    ~ImageScene() {}
    bool update();
private:

};

#endif
