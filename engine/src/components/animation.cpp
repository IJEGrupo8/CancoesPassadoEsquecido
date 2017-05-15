#include "components/animation.hpp"
#include "log.h"

using namespace engine;

bool AnimationComponent::init()
{
	m_current_frame = 0;
    ImageComponent::init();
    return true;
}

bool AnimationComponent::shutdown()
{
    ImageComponent::shutdown();

    return true;
}

bool AnimationComponent::setup(){
	m_current_frame = 0;
}

void AnimationComponent::draw()
{
	if(timer2.getTime() > 1000/16)
    {
		m_current_frame++;
		//m_current_frame = m_current_frame %15;
		timer2.startTimer();
	}
      
    INFO("xF = " << m_game_object->xF << " - yF = " << m_game_object->yF);

    int col = (m_current_frame%4)*m_game_object->w;
    int lin = (m_current_frame/4)*m_game_object->h;

    m_game_object->xF = col;
    m_game_object->yF = lin;

    ImageComponent::draw();
}




