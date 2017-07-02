#ifndef __ENGINE_TIMER__
#define __ENGINE_TIMER__

#include "sdl2include.h"

namespace engine {

class Timer
{
	public:
		Timer(): startTime(0) {}
		void startTimer(){startTime = SDL_GetTicks();}
		int getTime(){
			if(!stopped){
				lastRecorded = SDL_GetTicks() - startTime;
			}
			return lastRecorded;
		}
		void pauseTimer(){
			stopped = true;
		}
		void resumeTimer(){
			stopped = false;
		}

	private:
		Uint32 startTime;
		int lastRecorded;
		bool stopped = false;
};
}
#endif
