#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "Component.h"
#include "Animation.h"
#include <unordered_map>
#include <string>

class Animator : public Component {
public:
    Animator(GameObject& associated);
    void Update(float dt) override;
    void Render() override;
    void SetAnimation(std::string name);
    void AddAnimation(std::string name, Animation anim);
private:
    std::unordered_map<std::string, Animation> animations;
    int frameStart;
    int frameEnd;
    float frameTime;
    int currentFrame;
    float timeElapsed;
    SDL_FlipMode flip;
    std::string current;
};

#endif