#include "State.h"
#include "SDL3/SDL.h"
State::State(){
    this->quitRequested = false;
    bg.Open("resources/img/Background.png");
    music.Open("resources/audio/BGM.wav");
    music.Play();
}

void State::Update(float dt){
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            quitRequested = true;
        }
    }
}

void State::Render(){
    bg.Render(0,0);
}

bool State::QuitRequested(){
    return this->quitRequested;
}