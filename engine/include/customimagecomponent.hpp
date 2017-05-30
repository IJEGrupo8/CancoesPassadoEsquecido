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

        void setWidth(double width);
        void setHeight(double height);
        void setX(int x){m_x = x;}
        void setY(int y){m_y = y;}

    private:
        double m_width;
        double m_height;
        double m_x;
        double m_y;
    };

}

#endif
