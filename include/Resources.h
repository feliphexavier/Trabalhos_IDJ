#pragma once
#include <string>
#include <unordered_map>
#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>
class Resources {
public:
    static SDL_Texture* GetImage(std::string file);
    static void ClearImages();
    static MIX_Audio* GetMusic(std::string file);
    static void ClearMusics();
    static MIX_Audio* GetSound(std::string file);
    static void ClearSounds();

private:
    static std::unordered_map<std::string, SDL_Texture*> imageTable;
    static std::unordered_map<std::string, MIX_Audio*> musicTable;
    static std::unordered_map<std::string, MIX_Audio*> soundTable;
};
