#include "components/animationcontroller.hpp"
#include "log.h"

using namespace engine;

bool AnimationControllerComponent::init()
{
	for(auto animation : animations){
		animation.second.init();
	}
	return true;
}

bool AnimationControllerComponent::shutdown()
{
	for(auto animation : animations) {
		animation.second.shutdown();
	}
	return true;
}

bool AnimationControllerComponent::setup()
{
	return activeAnimation.setup();
}

void AnimationControllerComponent::draw(){
	activeAnimation.draw();
}

void AnimationControllerComponent::addAnimation(std::string name, AnimationComponent animation)
{
	INFO("Add a animação" << name);
	animations[name] = animation;
}
void AnimationControllerComponent::changeAnimation(std::string name)
{
	INFO("Trocando para a animação" << name);
	activeAnimation = animations[name];
	setup();
}
