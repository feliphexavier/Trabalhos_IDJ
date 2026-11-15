#include "Bullet.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include <cmath>
#include "Collider.h"
#include "Character.h"
#include "Zombie.h"
Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, bool targetsPlayer)
    : Component(associated), damage(damage), distanceLeft(maxDistance), targetsPlayer(targetsPlayer) {
    SpriteRenderer* renderer = new SpriteRenderer(associated, "resources/img/Bullet.png");
    associated.AddComponent(renderer);
    renderer->SetScale(2, 2);  
    this->speed = Vec2(std::cos(angle) * speed, std::sin(angle) * speed);
    associated.angleDeg = angle * 180.0 / M_PI + 90;   // item 1: sprite aponta para cima
}
void Bullet::Update(float dt) {
    float distance = speed.Magnitude() * dt;
    associated.box.x += speed.x * dt;
    associated.box.y += speed.y * dt;
    distanceLeft -= distance;
    if (distanceLeft <= 0) associated.RequestDelete();
}
void Bullet::Start() {
    associated.AddComponent(new Collider(associated));
}
void Bullet::Render() {}
int Bullet::GetDamage() { return damage; }

void Bullet::NotifyCollision(GameObject& other) {
    Character* ch = other.GetComponent<Character>();
    if (ch != nullptr) {
        if (targetsPlayer == (ch == Character::player)) associated.RequestDelete();
        return;
    }
    if (other.GetComponent<Zombie>() != nullptr && !targetsPlayer) {
        associated.RequestDelete();
    }
}