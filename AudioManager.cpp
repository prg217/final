#include "AudioManager.h"

AudioManager* AudioManager::s_pInstance = 0;

AudioManager::AudioManager() 
{
#ifdef WIN32
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
#endif
}
AudioManager::~AudioManager() {}

void AudioManager::playBGM()
{
#ifdef WIN32
	bgm = Mix_LoadMUS("Assets/EnchantedFestival.mp3");
	Mix_PlayMusic(bgm, -1);
	Mix_VolumeMusic(8);
#endif
}

void AudioManager::playEffect(Effect effect)
{
#ifdef WIN32
	switch (effect)
	{
	case Effect::s_attack:
		chu = Mix_LoadWAV("Assets/laser3.wav");
		Mix_VolumeChunk(chu, 5);
		Mix_PlayChannel(0, chu, 0);
		break;
	case Effect::s_hit:
		chu = Mix_LoadWAV("Assets/Futuristic Shotgun Single Shot.wav");
		Mix_VolumeChunk(chu, 3);
		Mix_PlayChannel(1, chu, 0);
		break;
	default:
		break;
	}
#endif
}