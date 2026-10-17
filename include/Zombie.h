#ifndef ZOMBIE_H
#define ZOMBIE_H
#include "Timer.h"
#include "Component.h"
#include "Sound.h"
class Zombie : public Component {
public:
    Zombie(GameObject& associated);
    void Damage(int damage);
    void Update(float dt) override;
    void Render() override;

private:
    int hitpoints;
    Sound deathSound;
    Sound hitSound;
    bool hit;          
    Timer hitTimer;    
    Timer deathTimer;
};
#endif