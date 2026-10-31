#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include "Component.h"
#include "Sprite.h"
#include <string>

class SpriteRenderer : public Component {
public:
    SpriteRenderer(GameObject& associated);
    SpriteRenderer(GameObject& associated, std::string file, int frameCountW = 1, int frameCountH = 1);
    void Open(std::string file);
    void SetFrameCount(int frameCountW, int frameCountH);
    void Update(float dt) override;
    void Render() override;
    void SetCameraFollower(bool cameraFollower);
    void SetScale(float scaleX, float scaleY);
    void SetFrame(int frame, SDL_FlipMode flip = SDL_FLIP_NONE);
private:
    Sprite sprite;
};

#endif