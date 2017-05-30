#include "components/audio.hpp"

#include "game.hpp"
#include "log.h"

using namespace engine;

bool AudioComponent::init()
{
    INFO("Init audio component");

    if (m_is_music)
    {
        m_music = Game::instance.asset_manager().load_music(m_path);
        if (m_music == NULL) return false;
    }
    else
    {
        m_sound = Game::instance.asset_manager().load_sound(m_path);
        if (m_sound == NULL) return false;
    }

    return true;
}

bool AudioComponent::shutdown()
{
    INFO("Shutdown audio component");
    return true;
}

bool AudioComponent::update()
{
    if(m_play_on_start)
    {
        play();
        m_play_on_start = false;
    }
    return true;
}

void AudioComponent::play(int loops, int channel)
{
	INFO("play");
    if(m_is_music)
    {
    	INFO("play music");
        if(m_audio_state == AudioState::stopped) Mix_PlayMusic(m_music, loops);
        else if (m_audio_state == AudioState::paused) Mix_ResumeMusic();
    }
    else
    {
    	INFO("play sound");
        if(m_audio_state == AudioState::stopped)
        {
        	INFO("play sound1");
            Mix_PlayChannel(channel, m_sound, loops);
        }
        else if (m_audio_state == AudioState::paused)
        {
        	INFO("play sound2");
            Mix_Resume(channel);
        }
    }

    m_audio_state = AudioState::playing;
}

void AudioComponent::stop(int channel)
{
    if(m_is_music) Mix_HaltMusic();
    else Mix_HaltChannel(channel);

    m_audio_state = AudioState::stopped;
}

void AudioComponent::pause(int channel)
{
    if(m_is_music) Mix_PauseMusic();
    else Mix_Pause(channel);

    m_audio_state = AudioState::paused;
}