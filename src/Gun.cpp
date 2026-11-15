#include "Gun.h"
#include "Bullet.h"
#include "Character.h"
#include "Game.h"
#include "State.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include <cmath>
#include <string>

Gun::Gun(GameObject& associated, std::weak_ptr<GameObject> character)
    : Component(associated),
      shotSound("resources/audio/Range.wav"),
      reloadSound("resources/audio/Hit0.wav"),
      cooldownState(0), character(character), angle(0) {
    associated.AddComponent(new SpriteRenderer(associated, "resources/img/Gun.png", 3, 2));
    Animator* animator = new Animator(associated);
    associated.AddComponent(animator);
    animator->AddAnimation("idle", Animation(0, 0, 0));
    animator->AddAnimation("reloading", Animation(1, 5, 0.1f));
    animator->AddAnimation("idleLeft", Animation(0, 0, 0, SDL_FLIP_VERTICAL));
    animator->AddAnimation("reloadingLeft", Animation(1, 5, 0.1f, SDL_FLIP_VERTICAL));
    animator->SetAnimation("idle");
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

    switch (cooldownState) {
    case 1:
        if (cdTimer.Get() > 0.3f) {
            cooldownState = 2;
            cdTimer.Restart();
            reloadSound.Play(1);
        }
        break;
    case 2:
        if (cdTimer.Get() > 0.5f) {
            cooldownState = 3;
            cdTimer.Restart();
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

    Animator* animator = associated.GetComponent<Animator>();
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

    Character* shooter = charObj->GetComponent<Character>();
    bool targetsPlayer = (shooter != Character::player);

    const float spread[3] = { -0.15f, 0.0f, 0.15f };
    for (int i = 0; i < 3; i++) {
        float bulletAngle = angle + spread[i];

        GameObject* bulletObject = new GameObject();
        bulletObject->AddComponent(new Bullet(*bulletObject, bulletAngle, 500, 10, 600, targetsPlayer));
        bulletObject->box.x = muzzle.x - bulletObject->box.w / 2;
        bulletObject->box.y = muzzle.y - bulletObject->box.h / 2;
        Game::GetInstance().GetState().AddObject(bulletObject);
    }
}

void Gun::Render() {}