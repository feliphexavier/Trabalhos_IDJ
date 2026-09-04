#include "Music.h"
#include <string>
#include <iostream>
#include "Game.h"

Music::Music(){
    music = nullptr;
    track = nullptr;
}

Music::Music(std::string file){
    music = nullptr;
    track = nullptr;
    Open(file);
}

void Music::Play(int times){
    if (music == nullptr){
        std::cout << "Erro ao buscar música" << SDL_GetError();
        return;
    }
    track = MIX_CreateTrack(Game::GetInstance().GetMixer());
    if(track == nullptr){
        std::cout << "ERro ao carregar track " << SDL_GetError();
        return ;
    }
    MIX_SetTrackAudio(track, music);
    SDL_PropertiesID options = SDL_CreateProperties();
    SDL_SetNumberProperty(options, MIX_PROP_PLAY_LOOPS_NUMBER, times);
    MIX_PlayTrack(track, options);
    SDL_DestroyProperties(options);

    

}
void Music::Stop(int msToStop) {
    if (track == nullptr) return;
    Sint64 frames = MIX_TrackMSToFrames(track,msToStop);
    MIX_StopTrack(track,frames);
}
void Music::Open(std::string file){
    music = MIX_LoadAudio(Game::GetInstance().GetMixer(), file.c_str(), false);
    if (music == nullptr){
        std::cout << "Erro ao abrir música: " << SDL_GetError() << std::endl;
    }
}
bool Music::IsOpen(){
    if (music == nullptr){
        return false;
    }
    return true;
}
Music::~Music(){
    if (music != nullptr){
MIX_DestroyAudio(music);
    }}