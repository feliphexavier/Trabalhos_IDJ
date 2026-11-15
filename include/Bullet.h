#ifndef BULLET_H
#define BULLET_H
#include "Component.h"
#include "Vec2.h"

class Bullet : public Component {
public:
    Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, bool targetsPlayer);
    void Update(float dt) override;
    void NotifyCollision(GameObject& other) override;
    void Render() override;
    int GetDamage();
    void Start() override;
    bool targetsPlayer;
private:
    Vec2 speed;
    float distanceLeft;
    int damage;
};

#endif