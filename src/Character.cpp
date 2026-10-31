#include "Character.h"
#include "Gun.h"
#include "Game.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "Camera.h"
Character* Character::player = nullptr;

Character::Command::Command(CommandType type, float x, float y)
    : type(type), pos(x, y) {}

Character::Character(GameObject& associated, std::string sprite)
    : Component(associated), speed(0, 0), linearSpeed(200), hp(100) {
    SpriteRenderer* renderer = new SpriteRenderer(associated, sprite, 3, 4);
    associated.AddComponent(renderer);
    Animator* animator = new Animator(associated);
    associated.AddComponent(animator);
    animator->AddAnimation("idle", Animation(9, 9, 0));
    animator->AddAnimation("walking", Animation(0, 8, 0.1f));
    animator->AddAnimation("dead", Animation(10, 10, 0));
    animator->SetAnimation("idle");
    facingLeft = false;
    animator->AddAnimation("idleLeft", Animation(9, 9, 0, SDL_FLIP_HORIZONTAL));
}

Character::~Character() {
    if (this == player) {
        player = nullptr;
        Camera::Unfollow();
    }
}

void Character::Start() {
    State& state = Game::GetInstance().GetState();
    std::weak_ptr<GameObject> self = state.GetObjectPtr(&associated);

    GameObject* gunObject = new GameObject();
    gunObject->AddComponent(new Gun(*gunObject, self));
    gun = state.AddObject(gunObject);
}

void Character::Issue(Command task) {
    taskQueue.push(task);
}

void Character::Update(float dt) {
    Animator* animator = associated.GetComponent<Animator>();
    if (hp <= 0) {
        while (!taskQueue.empty()) taskQueue.pop();
        if (animator != nullptr) animator->SetAnimation("dead");
        deathTimer.Update(dt);
        if (deathTimer.Get() > 2.0f) associated.RequestDelete();
        return;
    }
    
    Vec2 direction(0, 0);
    while (!taskQueue.empty()) {
        Command task = taskQueue.front();
        taskQueue.pop();

        if (task.type == Command::MOVE) {
            direction = direction.Sum(task.pos);
        } else if (task.type == Command::SHOOT) {
            std::shared_ptr<GameObject> gunObject = gun.lock();
            if (gunObject != nullptr) {
                Gun* gunCmp = gunObject->GetComponent<Gun>();
                if (gunCmp != nullptr) gunCmp->Shoot(task.pos);
            }
        }
    }
    bool moving = direction.Magnitude() > 0;
    if (moving) {
        speed = direction.Versor().Multiply(linearSpeed);
    } else {
        speed = Vec2(0, 0);
    }

    associated.box.x += speed.x * dt;
    associated.box.y += speed.y * dt;

    if (moving && speed.x != 0) facingLeft = speed.x < 0;

if (animator != nullptr) {
    std::string name = moving ? "walking" : "idle";
    if (facingLeft) name += "Left";
    animator->SetAnimation(name);}
}

void Character::Render() {}