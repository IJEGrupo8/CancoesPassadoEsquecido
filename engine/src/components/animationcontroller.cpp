#include "components/animationcontroller.hpp"
#include "log.h"

using namespace engine;

bool AnimationControllerComponent::init()
{
	for(auto animation : animations){
		INFO("INIT INIT");
		animation.second->init();
	}
	setup();
	return true;
}

bool AnimationControllerComponent::shutdown()
{
	for(auto animation : animations) {
		animation.second->shutdown();
	}
	return true;
}

bool AnimationControllerComponent::setup()
{
	return activeAnimation->setup();
}

void AnimationControllerComponent::draw(){
	//INFO("DRAW"<<activeAnimation.m_game_object->w << "   " << activeAnimation.m_game_object->h);
	activeAnimation->draw();
}

void AnimationControllerComponent::addAnimation(std::string name, AnimationComponent & animation)
{
	INFO("Add a animação" << name);
	if(animations.size() == 0) {
		activeAnimation = &animation;
	}
	animations[name] = &animation;
	//changeAnimation(name);
}
void AnimationControllerComponent::changeAnimation(std::string name)
{
	INFO("Trocando para a animação" << name);
	activeAnimation = animations[name];
	setup();
}
