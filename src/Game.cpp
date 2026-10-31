#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include "Game.h"
#include <iostream>
#include "Resources.h"
#include "InputManager.h"

Game* Game::instance = nullptr; 
static MIX_Mixer* mixer = nullptr;
Game::Game(std::string title, int width, int height) {
    instance = this;
    this->title = title;
    this->width = width;
    this->height = height;

    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        std::cout << "Erro ao iniciar o SDL: " << SDL_GetError() << std::endl;
    }

    if (!MIX_Init()) {
        std::cout << "Erro ao iniciar o Mixer: " << SDL_GetError() << std::endl;
    }

    mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
    if (mixer == nullptr) {
        std::cout << "Erro ao criar o mixer device: " << SDL_GetError() << std::endl;
    }

    window = SDL_CreateWindow(title.c_str(), width, height, 0);
    if (window == nullptr) {
        std::cout << "Erro ao criar a Janela: " << SDL_GetError() << std::endl;
    }

    renderer = SDL_CreateRenderer(window, nullptr);
    if (renderer == nullptr) {
        std::cout << "Erro ao criar o Renderer: " << SDL_GetError() << std::endl;
    }

    state = new State();

    frameStart = SDL_GetTicks();
    dt = 0;

}
Game& Game::GetInstance(){
    if (instance == nullptr){
        instance = new Game("221038945", 1200, 900);
    }
    return *instance;
    
}

Game::~Game(){
    delete state;
    MIX_DestroyMixer(mixer);
    MIX_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}

State& Game::GetState(){
    return *state;
}

SDL_Renderer* Game::GetRenderer(){
    return renderer;
}
MIX_Mixer* Game::GetMixer(){
    return mixer;
}

void Game::CalculateDeltaTime(){
    int previous = frameStart;
    frameStart = SDL_GetTicks();
    dt = (frameStart - previous) / 1000.0f;
    
}

float Game::GetDeltaTime(){
    return dt;
}

void Game::Run(){
    state->Start();
    while(!state->QuitRequested()){
        CalculateDeltaTime();
        SDL_RenderClear(renderer);
        InputManager::GetInstance().Update();
        state->Update(GetDeltaTime());
        state->Render();
        SDL_RenderPresent(renderer);
        SDL_Delay(33);
    }
    Resources::ClearImages();
    Resources::ClearMusics();
    Resources::ClearSounds();
}
