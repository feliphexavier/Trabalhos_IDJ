#include "Zombie.h"
#include "InputManager.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "iostream"
#include "Camera.h"
#include "Collider.h"
#include "Bullet.h"
#include "Character.h"
int Zombie::zombieCounter = 0;
Zombie::Zombie(GameObject& associated) : Component(associated),deathSound("resources/audio/Dead.wav"),hitSound("resources/audio/Hit0.wav"),hit(false) {
    hitpoints = 100;
    zombieCounter++;
    facingLeft = false;
    SpriteRenderer* spriteRenderer = new SpriteRenderer(associated, "resources/img/Enemy.png", 3, 2);
    associated.AddComponent(spriteRenderer);
    Animator* animator = new Animator(associated);
    associated.AddComponent(animator);
    animator->AddAnimation("walking", Animation(0, 3, 0.2f));
    animator->AddAnimation("dead", Animation(5, 5, 0));
    animator->AddAnimation("hit", Animation(4,4,0));
    animator->AddAnimation("walkingLeft", Animation(0, 3, 0.2f, SDL_FLIP_HORIZONTAL));
animator->AddAnimation("hitLeft", Animation(4, 4, 0, SDL_FLIP_HORIZONTAL));
animator->AddAnimation("deadLeft", Animation(5, 5, 0, SDL_FLIP_HORIZONTAL));
    animator->SetAnimation("walking");
}

void Zombie::Damage(int damage){
    if (hitpoints <= 0) return;

    hitpoints -= damage;
    hitSound.Play(1);
    Animator* animator = associated.GetComponent<Animator>();

    if (hitpoints <= 0) {
        if (animator != nullptr)
            animator->SetAnimation(facingLeft ? "deadLeft" : "dead");   // ← aqui
        deathSound.Play(1);
        deathTimer.Restart();

        Collider* collider = associated.GetComponent<Collider>();
        if (collider != nullptr) {
            associated.RemoveComponent(collider);
            delete collider;
        }
    } else {
        hit = true;
        hitTimer.Restart();
        if (animator != nullptr)
            animator->SetAnimation(facingLeft ? "hitLeft" : "hit");     // ← e aqui
    }
}

void Zombie::Update(float dt){
    hitTimer.Update(dt);
    InputManager& input = InputManager::GetInstance();

    Vec2 mouseWorld(input.GetMouseX() + Camera::pos.x,
                    input.GetMouseY() + Camera::pos.y);

  
    if (hit && hitpoints > 0 && hitTimer.Get() > 0.5f) {
    Animator* animator = associated.GetComponent<Animator>();
    if (animator != nullptr)
        animator->SetAnimation(facingLeft ? "walkingLeft" : "walking");
    hit = false;
}
    if (hitpoints <= 0) {
        deathTimer.Update(dt);
        if (deathTimer.Get() > 5.0f) {
            associated.RequestDelete();
        }
    }
    if (hitpoints > 0 && Character::player != nullptr) {
    Vec2 me(associated.box.x + associated.box.w / 2,
            associated.box.y + associated.box.h / 2);
    Vec2 dir = Character::player->GetCenter() - me;
    if (dir.Magnitude() > 1) {
        Vec2 velocity = dir.Versor() * 80;
        associated.box.x += velocity.x * dt;
        associated.box.y += velocity.y * dt;

        if (dir.x != 0) facingLeft = dir.x < 0;

        if (!hit) {
            Animator* animator = associated.GetComponent<Animator>();
            if (animator != nullptr)
                animator->SetAnimation(facingLeft ? "walkingLeft" : "walking");
        }
    }
}
}


void Zombie::Start() {
    associated.AddComponent(new Collider(associated, Vec2(0.6, 0.8), Vec2(0, 5)));
}

void Zombie::Render(){
}
void Zombie::NotifyCollision(GameObject& other) {
    Bullet* bullet = other.GetComponent<Bullet>();
    if (bullet != nullptr && !bullet->targetsPlayer) {
        Damage(bullet->GetDamage());
    }
}
Zombie::~Zombie() {
    zombieCounter--;
}