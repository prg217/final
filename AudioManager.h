#pragma once

#include "SDL.h"
#ifdef WIN32
#include "SDL_mixer.h"
#endif

enum Effect
{
    s_attack,
    s_hit
};

class AudioManager
{
public:
    static AudioManager* Instance()
    {
        if (s_pInstance == 0)
        {
            s_pInstance = new AudioManager();
            return s_pInstance;
        }
        return s_pInstance;
    }
    void playBGM();
    void playEffect(Effect effect);

private:
    AudioManager();
    ~AudioManager();
    static AudioManager* s_pInstance;
#ifdef WIN32
    Mix_Music* bgm; //배경음
    Mix_Chunk* chu; //효과음
#endif
};

typedef AudioManager TheAudioManager;