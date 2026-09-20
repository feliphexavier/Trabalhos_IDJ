#include "Zombie.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "Animator.h"

Zombie::Zombie(GameObject& associated) : Component(associated) {
    hitpoints = 100;
    SpriteRenderer* spriteRenderer = new SpriteRenderer(associated, "resources/img/Enemy.png", 3, 2);
    associated.AddComponent(spriteRenderer);
    Animator* animator = new Animator(associated);
    associated.AddComponent(animator);
    animator->AddAnimation("walking", Animation(0, 3, 10));
    animator->AddAnimation("dead", Animation(5, 5, 0));
    animator->SetAnimation("walking");
}

void Zombie::Damage(int damage){
    hitpoints -= damage;
    if (hitpoints <= 0) {
        Animator* animator = associated.GetComponent<Animator>();
        if (animator != nullptr) {
            animator->SetAnimation("dead");
        }
    }
}

void Zombie::Update(float dt){
    Damage(1);
}

void Zombie::Render(){
}