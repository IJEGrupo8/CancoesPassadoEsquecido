#ifndef __ENGINE_COMPONENTS_ANIMATION__
#define __ENGINE_COMPONENTS_ANIMATION__

#include <string>

#include "components/image.hpp"
#include "timer.hpp"
#include "gameobject.hpp"
namespace engine {
class GameObject;
class AnimationComponent : public ImageComponent {
public:
    AnimationComponent(GameObject & game_object, std::string path,int m_i, int m_j)
        : ImageComponent(game_object,path,m_i,m_j) {}

    AnimationComponent() : ImageComponent() {}

    ~AnimationComponent() {}

    bool init();
    bool shutdown();
    void draw();
    bool setup();

	Timer timer2;
	
    int linha = 0;
    int coluna = 0;
    int m_current_frame = 0;
};

}

#endif
