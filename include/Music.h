#ifndef MUSIC_H
#define MUSIC_H
#include <string>
#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>

class Music{
    public:
    Music();
    Music(std::string file);
    ~Music();
    void Play(int times = -1);
    void Stop(int msToStop = 1500);
    void Open(std::string file);
    bool IsOpen();
    private:
    MIX_Audio* music;
    MIX_Track* track;
};

#endif