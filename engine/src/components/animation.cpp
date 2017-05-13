#include "components/animation.hpp"

using namespace engine;

bool AnimationComponent::init()
{
    ImageComponent::init();
    return true;
}

bool AnimationComponent::shutdown()
{
    ImageComponent::shutdown();

    return true;
}

void AnimationComponent::draw()
{
    ImageComponent::draw();
}

