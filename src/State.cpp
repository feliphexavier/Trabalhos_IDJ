#include "State.h"
#include "SDL3/SDL.h"
#include "SpriteRenderer.h"
#include "Zombie.h"
#include "TileSet.h"
#include "TileMap.h"
#include "Component.h"
#include "InputManager.h"
#include "Camera.h"
#include <iostream>
#include "Character.h"
#include "PlayerController.h"
#include "Collider.h"
#include "Collision.h"
#include "WaveSpawner.h"
State::State() : quitRequested(false), started(false){
    GameObject* bg = new GameObject();
    bg->AddComponent(new SpriteRenderer(*bg, "resources/img/Background.png"));
    SpriteRenderer* bgRenderer = new SpriteRenderer(*bg, "resources/img/Background.png");
    bgRenderer->SetCameraFollower(true);
    bg->AddComponent(bgRenderer);
    bg->box.x = 0;
    bg->box.y = 0;
    AddObject(bg);
    GameObject* mapObject = new GameObject();
    mapObject->box.x = 0;
    mapObject->box.y = 0;
    TileSet* tileSet = new TileSet(64, 64, "resources/img/Tileset.png");
    mapObject->AddComponent(new TileMap(*mapObject, "resources/map/map.txt", tileSet));
    AddObject(mapObject);
    GameObject* charObject = new GameObject();
    Character* character = new Character(*charObject, "resources/img/Player.png");
    charObject->AddComponent(character);
    charObject->box.x = 1280 - charObject->box.w / 2;
    charObject->box.y = 1280 - charObject->box.h / 2;
    Character::player = character;
    charObject->AddComponent(new PlayerController(*charObject));
    AddObject(charObject);
    Camera::Follow(charObject);

    GameObject* spawnerObject = new GameObject();
    spawnerObject->AddComponent(new WaveSpawner(*spawnerObject));
    AddObject(spawnerObject);
}

State::~State(){
    objectArray.clear();
}
void State::Update(float dt){
    InputManager& input = InputManager::GetInstance();

    if (input.KeyPress(ESCAPE_KEY) || input.QuitRequested()) {
        quitRequested = true;
    }

    Camera::Update(dt);

    for (size_t i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }

    for (size_t i = 0; i < objectArray.size(); i++) {
        if (objectArray[i]->GetComponent<Collider>() == nullptr) continue;

        for (size_t j = i + 1; j < objectArray.size(); j++) {
            Collider* a = objectArray[i]->GetComponent<Collider>();
            if (a == nullptr) break;   // perdeu o collider (morreu): para de testar esse objeto

            Collider* b = objectArray[j]->GetComponent<Collider>();
            if (b == nullptr) continue;

            float angleA = objectArray[i]->angleDeg * M_PI / 180.0;
            float angleB = objectArray[j]->angleDeg * M_PI / 180.0;

            if (Collision::IsColliding(a->box, b->box, angleA, angleB)) {
                objectArray[i]->NotifyCollision(*objectArray[j]);
                objectArray[j]->NotifyCollision(*objectArray[i]);
            }
        }
    }

    for (int i = (int)objectArray.size() - 1; i >= 0; i--) {
        if (objectArray[i]->IsDead()) {
            objectArray.erase(objectArray.begin() + i);
        }
    }
}
void State::LoadAssets(){
    music.Open("resources/audio/BGM.wav");
    music.Play();
}

void State::Render(){


    for (size_t i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Render();
    }
}

bool State::QuitRequested(){
    return quitRequested;
}


void State::Start() {
    LoadAssets();
    for (size_t i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Start();
    }
    started = true;
}

std::weak_ptr<GameObject> State::AddObject(GameObject* go) {
    std::shared_ptr<GameObject> ptr(go);
    objectArray.push_back(ptr);
    if (started) ptr->Start();
    return std::weak_ptr<GameObject>(ptr);
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go) {
    for (auto& obj : objectArray) {
        if (obj.get() == go) return std::weak_ptr<GameObject>(obj);
    }
    return std::weak_ptr<GameObject>();
}

