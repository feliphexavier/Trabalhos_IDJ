#include "SpriteRenderer.h"
#include "GameObject.h"
#include <iostream>
SpriteRenderer::SpriteRenderer(GameObject& associated) : Component(associated) {
}

SpriteRenderer::SpriteRenderer(GameObject& associated, std::string file, int frameCountW, int frameCountH)
    : Component(associated) {
    sprite.Open(file);
    sprite.SetFrameCount(frameCountW, frameCountH);
    std::cout << file << " " << sprite.GetWidth() << "x" << sprite.GetHeight() << std::endl;
    this->associated.box.w = sprite.GetWidth();
    this->associated.box.h = sprite.GetHeight();
    SetFrame(0);
}

void SpriteRenderer::SetFrame(int frame, SDL_FlipMode flip){
    sprite.SetFrame(frame);
    sprite.SetFlip(flip);
}
void SpriteRenderer::Open(std::string file){
    sprite.Open(file);
    this->associated.box.w = sprite.GetWidth();
    this->associated.box.h = sprite.GetHeight();
}

void SpriteRenderer::SetFrameCount(int frameCountW, int frameCountH){
    sprite.SetFrameCount(frameCountW, frameCountH);
}


void SpriteRenderer::Update(float dt){
}

void SpriteRenderer::Render(){
    sprite.Render(associated.box.x, associated.box.y,
                  associated.box.w, associated.box.h,
                  associated.angleDeg);
}

void SpriteRenderer::SetCameraFollower(bool cameraFollower){
    sprite.cameraFollower = cameraFollower;
}

void SpriteRenderer::SetScale(float scaleX, float scaleY){
    float cx = associated.box.x + associated.box.w / 2;
    float cy = associated.box.y + associated.box.h / 2;

    sprite.SetScale(scaleX, scaleY);

    associated.box.w = sprite.GetWidth();
    associated.box.h = sprite.GetHeight();

    associated.box.x = cx - associated.box.w / 2;
    associated.box.y = cy - associated.box.h / 2;
}
