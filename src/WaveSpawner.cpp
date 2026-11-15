#include "WaveSpawner.h"
#include "GameObject.h"
#include "Zombie.h"
#include "Character.h"
#include "AIController.h"
#include "Camera.h"
#include "Game.h"
#include "State.h"
#include <cstdlib>
#include <cmath>

WaveSpawner::WaveSpawner(GameObject& associated)
    : Component(associated), zombieCounter(0), currentWave(0) {
    waves.emplace_back(3, 3.0f);
    waves.emplace_back(5, 2.5f);
    waves.emplace_back(8, 2.0f);
}

void WaveSpawner::Update(float dt) {
    zombieCooldownTimer.Update(dt);

    if (currentWave >= (int)waves.size()) {
        associated.RequestDelete();
        return;
    }

    Wave& wave = waves[currentWave];

    if (zombieCounter < wave.zombies) {
        if (zombieCooldownTimer.Get() > wave.cooldown) {
            Vec2 base(Camera::pos.x + 600, Camera::pos.y + 450);
            if (Character::player != nullptr) base = Character::player->GetCenter();

            float angle = (rand() / (float)RAND_MAX) * 2 * M_PI;
            Vec2 pos(base.x + 850 * std::cos(angle), base.y + 850 * std::sin(angle));

            bool spawnNPC = (zombieCounter % 4 == 3);

            GameObject* enemy = new GameObject();
            if (spawnNPC) {
                enemy->AddComponent(new Character(*enemy, "resources/img/NPC.png"));
                enemy->AddComponent(new AIController(*enemy));
            } else {
                enemy->AddComponent(new Zombie(*enemy));
            }
            enemy->box.x = pos.x - enemy->box.w / 2;
            enemy->box.y = pos.y - enemy->box.h / 2;
            Game::GetInstance().GetState().AddObject(enemy);

            zombieCounter++;
            zombieCooldownTimer.Restart();
        }
    } else if (Zombie::zombieCounter == 0 && AIController::npcCounter == 0) {
        currentWave++;
        zombieCounter = 0;
        zombieCooldownTimer.Restart();
    }
}

void WaveSpawner::Render() {}