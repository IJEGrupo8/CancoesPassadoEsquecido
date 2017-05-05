#ifndef __ENGINE_TIMER__
#define __ENGINE_TIMER__

#include "sdl2include.h"

namespace engine {

class Timer
{
	public:
		Timer(): startTime(0) {}
		void startTimer(){startTime = SDL_GetTicks();}
		int getTime(){return SDL_GetTicks() - startTime;}

		
	private:
		Uint32 startTime;
};
}
#endif
