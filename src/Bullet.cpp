#include "Bullet.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include <cmath>

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance)
    : Component(associated), damage(damage), distanceLeft(maxDistance) {
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
void Bullet::Render() {}
int Bullet::GetDamage() { return damage; }