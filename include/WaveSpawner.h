#ifndef WAVESPAWNER_H
#define WAVESPAWNER_H

#include <vector>
#include "Component.h"
#include "Timer.h"

class Wave {
public:
    Wave(int zombies, float cooldown) : zombies(zombies), cooldown(cooldown) {}
    int zombies;
    float cooldown;
};

class WaveSpawner : public Component {
public:
    WaveSpawner(GameObject& associated);
    void Update(float dt) override;
    void Render() override;

private:
    int zombieCounter;
    std::vector<Wave> waves;
    Timer zombieCooldownTimer;
    int currentWave;
};

#endif