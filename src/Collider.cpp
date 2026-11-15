#include "Collider.h"
#include "GameObject.h"
#include <cmath>

#ifdef DEBUG
#include <SDL3/SDL.h>
#include "Camera.h"
#include "Game.h"
#endif

Collider::Collider(GameObject& associated, Vec2 scale, Vec2 offset)
    : Component(associated), scale(scale), offset(offset) {}

void Collider::Update(float dt) {
    box = associated.box;
    box.w *= scale.x;
    box.h *= scale.y;

    float rad = associated.angleDeg * M_PI / 180.0;
    Vec2 rotated(offset.x * std::cos(rad) - offset.y * std::sin(rad),
                 offset.x * std::sin(rad) + offset.y * std::cos(rad));
    Vec2 center(associated.box.x + associated.box.w / 2 + rotated.x,
                associated.box.y + associated.box.h / 2 + rotated.y);

    box.x = center.x - box.w / 2;
    box.y = center.y - box.h / 2;
}

void Collider::Render() {
#ifdef DEBUG
    Vec2 center = box.GetCenter();
    float rad = associated.angleDeg * M_PI / 180.0;
    float cs = std::cos(rad), sn = std::sin(rad);

    Vec2 corners[4] = {
        Vec2(box.x, box.y),
        Vec2(box.x + box.w, box.y),
        Vec2(box.x + box.w, box.y + box.h),
        Vec2(box.x, box.y + box.h)
    };

    SDL_FPoint points[5];
    for (int i = 0; i < 4; i++) {
        Vec2 d = corners[i] - center;
        Vec2 p(d.x * cs - d.y * sn + center.x - Camera::pos.x,
               d.x * sn + d.y * cs + center.y - Camera::pos.y);
        points[i] = { p.x, p.y };
    }
    points[4] = points[0];   

    SDL_Renderer* renderer = Game::GetInstance().GetRenderer();
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderLines(renderer, points, 5);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);   // devolve a cor de limpeza
#endif
}

void Collider::SetScale(Vec2 scale) { this->scale = scale; }
void Collider::SetOffset(Vec2 offset) { this->offset = offset; }