#ifndef ANIMATION_H
#define ANIMATION_H
#include <SDL3/SDL.h>

class Animation {
public:
    Animation(int frameStart, int frameEnd, float frameTime, SDL_FlipMode flip = SDL_FLIP_NONE);
    int frameStart;
    int frameEnd;
    float frameTime;
    SDL_FlipMode flip;
};

#endif