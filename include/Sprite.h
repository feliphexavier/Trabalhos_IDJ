#ifndef SPRITE_H
#define SPRITE_H
#include <string>
#include <SDL3/SDL.h>
#include "Vec2.h"
class Sprite{
    public: 
    Sprite();
    Sprite(std::string file, int frameCountW = 1, int frameCountH = 1);    
    ~Sprite();
    void Open(std::string file);
    void SetClip(int x, int y, int w, int h);
    void Render(int x, int y, int w, int h, float angle=0);
    int GetWidth();
    int GetHeight();
    bool IsOpen();
    void SetFrame(int frame);
    void SetFrameCount(int frameCountW, int frameCountH);
    bool cameraFollower;
    void SetScale(float scaleX, float scaleY);
    Vec2 GetScale();
    void SetFlip(SDL_FlipMode flip);
    private:
    SDL_Texture* texture;
    int width;
    int height;
    SDL_FRect clipRect;
    int frameCountW;
    int frameCountH;
    SDL_FlipMode flip;
    Vec2 scale;
};
#endif