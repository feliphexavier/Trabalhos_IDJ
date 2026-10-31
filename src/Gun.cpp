#include "Gun.h"
#include "Bullet.h"
#include "Game.h"
#include "State.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include <cmath>
Gun::Gun(GameObject& associated, std::weak_ptr<GameObject> character)
    : Component(associated),
      shotSound("resources/audio/Range.wav"),
      reloadSound("resources/audio/Hit0.wav"),
      cooldownState(0), character(character), angle(0) {
    associated.AddComponent(new SpriteRenderer(associated, "resources/img/Gun.png", 3, 2));
    Animator* animator = new Animator(associated);
    associated.AddComponent(animator);
    animator->AddAnimation("idle", Animation(0, 0, 0));
    animator->AddAnimation("reloading", Animation(1, 5, 0.2f));
    animator->SetAnimation("idle");
    animator->AddAnimation("idleLeft", Animation(0, 0, 0, SDL_FLIP_VERTICAL));
    animator->AddAnimation("reloadingLeft", Animation(1, 5, 0.1f, SDL_FLIP_VERTICAL));
}

void Gun::Update(float dt) {
    std::shared_ptr<GameObject> charObj = character.lock();
    if (charObj == nullptr) {
        associated.RequestDelete();
        return;
    }
    Vec2 charCenter(charObj->box.x + charObj->box.w / 2,
                    charObj->box.y + charObj->box.h / 2);
    const float distance = 40;  
    Vec2 center(charCenter.x + distance * std::cos(angle),
                charCenter.y + distance * std::sin(angle));
    associated.box.x = center.x - associated.box.w / 2;
    associated.box.y = center.y - associated.box.h / 2;

    associated.angleDeg = angle * 180.0 / M_PI;

    bool left = std::cos(angle) < 0;
    cdTimer.Update(dt);
    Animator* animator = associated.GetComponent<Animator>();

    switch (cooldownState) {
    case 1:   
        if (cdTimer.Get() > 0.3f) {
            cooldownState = 2;
            cdTimer.Restart();
            reloadSound.Play(1);
            if (animator != nullptr) animator->SetAnimation("reloading");
        }
        break;
    case 2:   
        if (cdTimer.Get() > 0.5f) {
            cooldownState = 3;
            cdTimer.Restart();
            if (animator != nullptr) animator->SetAnimation("idle");
        }
        break;
    case 3:   
        if (cdTimer.Get() > 0.2f) {
            cooldownState = 0;
        }
        break;
    default:  
        break;
    }
    if (animator != nullptr) {
    std::string name = (cooldownState == 2) ? "reloading" : "idle";
    if (left) name += "Left";
    animator->SetAnimation(name);
}
}

void Gun::Shoot(Vec2 target) {
    if (cooldownState != 0) return;

    std::shared_ptr<GameObject> charObj = character.lock();
    if (charObj == nullptr) return;

    Vec2 charCenter(charObj->box.x + charObj->box.w / 2,
                    charObj->box.y + charObj->box.h / 2);
    angle = std::atan2(target.y - charCenter.y, target.x - charCenter.x);

    shotSound.Play(1);
    cooldownState = 1;
    cdTimer.Restart();

    const float gunDistance = 40;   
    float barrel = gunDistance + associated.box.w / 2;
    Vec2 muzzle(charCenter.x + barrel * std::cos(angle),
                charCenter.y + barrel * std::sin(angle));

    GameObject* bulletObject = new GameObject();
    bulletObject->AddComponent(new Bullet(*bulletObject, angle, 500, 10, 600));
    bulletObject->box.x = muzzle.x - bulletObject->box.w / 2;
    bulletObject->box.y = muzzle.y - bulletObject->box.h / 2;
    Game::GetInstance().GetState().AddObject(bulletObject);
}
void Gun::Render() {}