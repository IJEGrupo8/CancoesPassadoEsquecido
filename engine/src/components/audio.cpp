#include "components/audio.hpp"

#include "game.hpp"
#include "log.h"
#include "sdl_log.h"

using namespace engine;

bool AudioComponent::init()
{
	sound = Mix_LoadWAV( "assets/pika.wav" );
	if(sound == NULL){
		WARN("Não carregou\n");
		return false;
	}
	return true;
}
bool AudioComponent::shutdown()
{
	Mix_FreeChunk(sound);
	INFO("AudioComponent shutdown");
}
void AudioComponent::play()
{
	if(Mix_PlayChannel( -1, sound, 0 )==-1){
		WARN("Não Tocou\n");
	}
}