#include "State.h"
#include "SDL3/SDL.h"
#include "SpriteRenderer.h"
#include "Zombie.h"
State::State(){
    quitRequested = false;
    music.Open("resources/audio/BGM.wav");
    music.Play();

    GameObject* bgObject = new GameObject();
    SpriteRenderer* bgRenderer = new SpriteRenderer(*bgObject, "resources/img/Background.png");
    bgObject->AddComponent(bgRenderer);
    AddObject(bgObject);

    GameObject* zombieObject = new GameObject();
    zombieObject->box.x = 600;
    zombieObject->box.y = 450;
    Zombie* zombie = new Zombie(*zombieObject);
    zombieObject->AddComponent(zombie);
    AddObject(zombieObject);
}

State::~State(){
    objectArray.clear();
}
void State::Update(float dt){
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            quitRequested = true;
        }
    }

    for (auto& go : objectArray) {
        go->Update(dt);
    }

    for (int i = (int)objectArray.size() - 1; i >= 0; i--) {
        if (objectArray[i]->IsDead()) {
            objectArray.erase(objectArray.begin() + i);
        }
    }
}

void State::Render(){
    for (auto& go : objectArray) {
        go->Render();
    }
}

bool State::QuitRequested(){
    return quitRequested;
}

void State::AddObject(GameObject* go){
    objectArray.emplace_back(go);
}