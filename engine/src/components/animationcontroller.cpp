#include "components/animationcontroller.hpp"
#include "log.h"

using namespace engine;

bool AnimationControllerComponent::init()
{
		INFO("INIT AC");

	for(auto animation : animations){
		animation.second.init();
	}
	return true;
}

bool AnimationControllerComponent::shutdown()
{
		INFO("SD AC");

	for(auto animation : animations) {
		animation.second.shutdown();
	}
	return true;
}

bool AnimationControllerComponent::setup()
{
		INFO("SETUP AC");

	return activeAnimation->setup();
}

void AnimationControllerComponent::draw(){
	INFO("DRAW AC");
	activeAnimation->draw();
}

void AnimationControllerComponent::addAnimation(std::string name, AnimationComponent animation)
{
	INFO("Add a animação" << name);
	if(animations.size() == 0) {
		activeAnimation = &animation;
	}
	animations[name] = animation;
}
void AnimationControllerComponent::changeAnimation(std::string name)
{
	INFO("Trocando para a animação" << name);
	activeAnimation = &animations[name];
	setup();
}
