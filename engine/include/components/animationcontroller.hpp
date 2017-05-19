#ifndef __ENGINE_COMPONENTS_ANIMATION_CONTROLLER__
#define __ENGINE_COMPONENTS_ANIMATION_CONTROLLER__

#include <string>

#include "components/image.hpp"
#include "timer.hpp"
#include "gameobject.hpp"
#include "animation.hpp"

namespace engine {
class GameObject;
class AnimationControllerComponent : public ImageComponent {
public:
    AnimationControllerComponent(GameObject & game_object, std::string path, int m_i, int m_j)
        : ImageComponent(game_object, path, m_i, m_j) {}

    AnimationControllerComponent() : ImageComponent() {}

    ~AnimationControllerComponent() {}

    bool init();
    bool shutdown();
    void draw();
    bool setup();
    void addAnimation(std::string name, AnimationComponent animation);
    void changeAnimation(std::string name);

    AnimationComponent activeAnimation;
    std::unordered_map<std::string, AnimationComponent > animations;
};

}

#endif
