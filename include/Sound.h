#pragma once
#include <string>
#include <SDL3_mixer/SDL_mixer.h>

class Sound {
public:
    Sound();
    Sound(std::string file);
    ~Sound();
    void Play(int times = 1);
    void Stop();
    void Open(std::string file);
    bool IsOpen();
private:
    MIX_Audio* chunk;
    MIX_Track* track;
};