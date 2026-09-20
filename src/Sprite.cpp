#include "Sprite.h"
#include "SDL3/SDL.h"
#include <SDL3_image/SDL_image.h>
#include "Game.h"
#include <iostream>

Sprite::Sprite(){
    texture = nullptr;
    frameCountW = 1;
    frameCountH = 1;
}
Sprite::Sprite(std::string file, int frameCountW, int frameCountH){
    texture = nullptr;
    Open(file);
    SetFrameCount(frameCountW, frameCountH);
    SetFrame(0);
}
Sprite::~Sprite(){
    if(texture != nullptr){
        SDL_DestroyTexture(texture);
    }
}
void Sprite::Open(std::string file){
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
    texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
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

void Sprite::Render(int x, int y, int w, int h){
    SDL_FRect dstrect;
    dstrect.x = (float)x;
    dstrect.y = (float)y;
    dstrect.w = (float)w;
    dstrect.h = (float)h;

    SDL_RenderTexture(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstrect);
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

int Sprite::GetWidth(){
    return width / frameCountW;
}

int Sprite::GetHeight(){
    return height / frameCountH;
}

bool Sprite::IsOpen(){
    if (texture != nullptr){
        return true;
    }
    return false;
}