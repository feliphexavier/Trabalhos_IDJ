#include "Animator.h"
#include "GameObject.h"
#include "SpriteRenderer.h"

Animator::Animator(GameObject& associated) : Component(associated) {
    frameStart = 0;
    frameEnd = 0;
    frameTime = 0;
    currentFrame = 0;
    timeElapsed = 0;
}
void Animator::Update(float dt){
    if (frameTime == 0) {
        return;
    }
    timeElapsed += dt;
    if (timeElapsed > frameTime) {
        currentFrame++;
        timeElapsed -= frameTime;
        if (currentFrame > frameEnd) {
            currentFrame = frameStart;
        }
        SpriteRenderer* spriteRenderer = associated.GetComponent<SpriteRenderer>();
        if (spriteRenderer != nullptr) {
            spriteRenderer->SetFrame(currentFrame);
        }
    }
}

void Animator::Render(){
    
}
void Animator::SetAnimation(std::string name){
    auto it = animations.find(name);
    if (it != animations.end()) {
        Animation anim = it->second;
        frameStart = anim.frameStart;
        frameEnd = anim.frameEnd;
        frameTime = anim.frameTime;
        currentFrame = frameStart;
        timeElapsed = 0;
        SpriteRenderer* spriteRenderer = associated.GetComponent<SpriteRenderer>();
        if (spriteRenderer != nullptr) {
            spriteRenderer->SetFrame(currentFrame);
        }
    }
}
void Animator::AddAnimation(std::string name, Animation anim){
    if (animations.find(name) == animations.end()) {
        animations.emplace(name, anim);
    }
}