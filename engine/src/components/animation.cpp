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
	clock.startTimer();
	m_loop = loop;

	return true;
}

void AnimationComponent::draw()
{
	if(m_loop == -1 || m_loop > 0){
		if(clock.getTime() < duration){
			drawFrame();
			
		}else{
			if(m_loop > 0)
			{
				m_loop--;
			}
			drawFrame();	
			clock.startTimer();
		}
	}else{
		INFO("Loops ended");

	}
}

void AnimationComponent::drawFrame(){
	m_current_frame = ((clock.getTime()/animationFrameTime)+start_frame);
	//m_current_frame = m_current_frame %15;
	
	//INFO("xF = " << m_game_object->xF << " - yF = " << m_game_object->yF <<"  -mF = "  << m_current_frame);

    int col = (m_current_frame%n_lines)*m_game_object->w;
    int lin = (m_current_frame/n_cols)*m_game_object->h;

	//INFO("W = " << m_game_object->w << " - H = " << m_game_object->h);

    m_game_object->xF = col;
    m_game_object->yF = lin;
	//INFO("X = " << m_game_object->physics.position.getX() << " - Y = " << m_game_object->physics.position.getY());

    ImageComponent::draw();
}


