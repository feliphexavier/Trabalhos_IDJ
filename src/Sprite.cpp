#include "Sprite.h"
#include "SDL3/SDL.h"
#include <SDL3_image/SDL_image.h>
#include "Game.h"
#include <iostream>
#include "Resources.h"
#include "Camera.h"
Sprite::Sprite(){
    cameraFollower = false;
    texture = nullptr;
    frameCountW = 1;
    frameCountH = 1;
    scale.x = 1;
    scale.y = 1;
    flip = SDL_FLIP_NONE;
}
Sprite::Sprite(std::string file, int frameCountW, int frameCountH){
    cameraFollower = false;
    texture = nullptr;
    scale.x = 1;
    scale.y = 1;
    flip = SDL_FLIP_NONE;
    Open(file);
    SetFrameCount(frameCountW, frameCountH);
    SetFrame(0);
}
Sprite::~Sprite(){
    
}
void Sprite::Open(std::string file){
    if (texture != nullptr) {

        texture = nullptr;
    }
    texture = Resources::GetImage(file);
    if (texture == nullptr) {
        std::cout << "Erro ao carregar textura: " << SDL_GetError() << std::endl;
        return;
    }
    width = texture->w;
    height = texture->h;
    
    clipRect.x = 0;
    clipRect.y = 0;
    clipRect.w = width;
    clipRect.h = height;
    frameCountW = 1;
    frameCountH = 1;
}

void Sprite::SetClip(int x, int y, int w, int h){
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render(int x, int y, int w, int h, float angle){
    if (texture == nullptr) return;
    SDL_FRect dstrect;
    dstrect.w = (float)w;
    dstrect.h = (float)h;
    if (cameraFollower) {
        dstrect.x = x;
        dstrect.y = y;
    } else {
        dstrect.x = x - Camera::pos.x;
        dstrect.y = y - Camera::pos.y;
    }
    if (!SDL_RenderTextureRotated(Game::GetInstance().GetRenderer(), texture,
                                  &clipRect, &dstrect, angle, nullptr, flip)) {
        std::cout << "Render falhou: " << SDL_GetError() << std::endl;
    }
}
void Sprite::SetScale(float scaleX, float scaleY){
    if (scaleX != 0) scale.x = scaleX;
    if (scaleY != 0) scale.y = scaleY;
}

void Sprite::SetFrameCount(int frameCountW, int frameCountH){
    this->frameCountW = frameCountW;
    this->frameCountH = frameCountH;
}

void Sprite::SetFrame(int frame){
    int frameW = width / frameCountW;
    int frameH = height / frameCountH;

    int row = frame / frameCountW;
    int col = frame % frameCountW;

    int frameX = col * frameW;
    int frameY = row * frameH;
    if (frameX + frameW > width || frameY + frameH > height) {
        std::cout << "SetFrame: frame " << frame << " fora dos limites da imagem" << std::endl;
        return;
    }

    SetClip(frameX, frameY, frameW, frameH);
}

Vec2 Sprite::GetScale(){
    return scale;
}

void Sprite::SetFlip(SDL_FlipMode flip){
    this->flip = flip;
}

int Sprite::GetWidth(){
    return (width / frameCountW) * scale.x;
}

int Sprite::GetHeight(){
    return (height / frameCountH) * scale.y;
}

bool Sprite::IsOpen(){
    if (texture != nullptr){
        return true;
    }
    return false;
}