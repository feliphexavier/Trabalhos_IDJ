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

State::State() : quitRequested(false){
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
    
    LoadAssets();
}

State::~State(){
    objectArray.clear();
}
void State::Update(float dt){
    InputManager& input = InputManager::GetInstance();

    if (input.KeyPress(ESCAPE_KEY) || input.QuitRequested()) {
        quitRequested = true;
    }

    if (input.KeyPress(SPACE_KEY)) {
        GameObject* zombieObject = new GameObject();
        zombieObject->AddComponent(new Zombie(*zombieObject));
        zombieObject->box.x = input.GetMouseX() + Camera::pos.x;
        zombieObject->box.y = input.GetMouseY() + Camera::pos.y;
        AddObject(zombieObject);
    }
    Camera::Update(dt);

    for (size_t i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Update(dt);
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

void State::AddObject(GameObject* go){
    objectArray.emplace_back(go);
}