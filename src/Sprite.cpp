#include "Sprite.h"
#include "SDL3/SDL.h"
#include <SDL3_image/SDL_image.h>
#include "Game.h"
#include <iostream>

Sprite::Sprite(){
    texture = nullptr; 
}
Sprite::Sprite(std::string file){
    texture = nullptr;
    Open(file);
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
}

void Sprite::SetClip(int x, int y, int w, int h){
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render(int x, int y){
    SDL_FRect dstrect;
    dstrect.x = x;
    dstrect.y = y;
    dstrect.h = clipRect.h;
    dstrect.w = clipRect.w;

    SDL_RenderTexture(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstrect);
}

int Sprite::GetWidth(){
    return width;
}
int Sprite::GetHeight(){
    return height;
}

bool Sprite::IsOpen(){
    if (texture != nullptr){
        return true;
    }
    return false;
}