#include "Sound.h"
#include "Game.h"
#include <iostream>

Sound::Sound() : chunk(nullptr), track(nullptr) {}
Sound::Sound(std::string file) : Sound() {
    Open(file);
}
Sound::~Sound() {
    if (chunk != nullptr) {
        Stop();
        MIX_DestroyTrack(track);
        MIX_DestroyAudio(chunk);
    }
}
void Sound::Open(std::string file) {
    MIX_Mixer* mixer = Game::GetInstance().GetMixer(); 
    chunk = MIX_LoadAudio(mixer, file.c_str(), true);
    if (chunk == nullptr) {
        std::cerr << "Sound: falha ao abrir " << file << ": " << SDL_GetError() << std::endl;
        return;
    }
    track = MIX_CreateTrack(mixer);
    if (track == nullptr) {
        std::cerr << "Sound: falha ao criar track: " << SDL_GetError() << std::endl;
        return;
    }
    MIX_SetTrackAudio(track, chunk);
}
void Sound::Play(int times) {
    if (track == nullptr) return;
    SDL_PropertiesID props = SDL_CreateProperties();
    SDL_SetNumberProperty(props, MIX_PROP_PLAY_LOOPS_NUMBER, times - 1);
    MIX_PlayTrack(track, props);
    SDL_DestroyProperties(props);
}
void Sound::Stop() {
    if (track != nullptr) {
        MIX_StopTrack(track, 0);   
    }
}
bool Sound::IsOpen() {
    return chunk != nullptr;
}