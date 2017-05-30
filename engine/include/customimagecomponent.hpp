#ifndef __ENGINE_CUSTOM_IMAGE_COMPONENT__
#define __ENGINE_CUSTOM_IMAGE_COMPONENT__

#include <string>
#include "gameobject.hpp"
#include "components/image.hpp"
#include "game.hpp"

namespace engine {

class GameObject;

class CustomImageComponent : public ImageComponent{
    public:

        CustomImageComponent(GameObject & game_object, std::string path,int m_i, int m_j):
        ImageComponent(game_object, path,m_i,m_j){}

        virtual ~CustomImageComponent(){}

        virtual bool init();
        virtual bool shutdown();
        virtual void draw();

        void setWidth(int width);
        void setHeight(int height);

    private:
        int m_width;
        int m_height;
    };

}

#endif
