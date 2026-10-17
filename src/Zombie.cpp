#include "Zombie.h"
#include "InputManager.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "iostream"
#include "Camera.h"
Zombie::Zombie(GameObject& associated) : Component(associated),deathSound("resources/audio/Dead.wav"),hitSound("resources/audio/Hit0.wav"),hit(false) {
    hitpoints = 100;
    SpriteRenderer* spriteRenderer = new SpriteRenderer(associated, "resources/img/Enemy.png", 3, 2);
    associated.AddComponent(spriteRenderer);
    Animator* animator = new Animator(associated);
    associated.AddComponent(animator);
    animator->AddAnimation("walking", Animation(0, 3, 0.2f));
    animator->AddAnimation("dead", Animation(5, 5, 0));
    animator->AddAnimation("hit", Animation(4,4,0));
    animator->SetAnimation("walking");
}

void Zombie::Damage(int damage){
    
    if (hitpoints <= 0) return;   

    hitpoints -= damage;
    hitSound.Play(1);
    
    Animator* animator = associated.GetComponent<Animator>();

    if (hitpoints <= 0) {
        if (animator != nullptr) animator->SetAnimation("dead");
        deathSound.Play(1);
        deathTimer.Restart();
    } else {
        hit = true;
        hitTimer.Restart();
        if (animator != nullptr) animator->SetAnimation("hit");
    }
}

void Zombie::Update(float dt){
    hitTimer.Update(dt);
    InputManager& input = InputManager::GetInstance();

    Vec2 mouseWorld(input.GetMouseX() + Camera::pos.x,
                    input.GetMouseY() + Camera::pos.y);

    if (input.MousePress(LEFT_MOUSE_BUTTON) &&
        associated.box.IsInside(mouseWorld)) {

        Damage(10);
    }
    if (hit && hitpoints > 0 && hitTimer.Get() > 0.5f) {
        Animator* animator = associated.GetComponent<Animator>();
        if (animator != nullptr) animator->SetAnimation("walking");
        hit = false;
    }
    if (hitpoints <= 0) {
        deathTimer.Update(dt);
        if (deathTimer.Get() > 5.0f) {
            associated.RequestDelete();
        }
    }
}

void Zombie::Render(){
}