#include "State.h"
#include "SDL3/SDL.h"
#include "SpriteRenderer.h"
#include "Zombie.h"
#include "TileSet.h"
#include "TileMap.h"
#include "Component.h"

State::State() : quitRequested(false){
    GameObject* bg = new GameObject();
    bg->AddComponent(new SpriteRenderer(*bg, "resources/img/Background.png"));
    bg->box.x = 0;
    bg->box.y = 0;
    AddObject(bg);
    GameObject* mapObject = new GameObject();
    mapObject->box.x = 0;
    mapObject->box.y = 0;
    TileSet* tileSet = new TileSet(64, 64, "resources/img/Tileset.png");
    mapObject->AddComponent(new TileMap(*mapObject, "resources/map/map.txt", tileSet));
    AddObject(mapObject);
    for (int i = 0; i < 3; i++) {
        GameObject* zombieObject = new GameObject();
        zombieObject->AddComponent(new Zombie(*zombieObject));
        zombieObject->box.x = 300 + i * 200;
        zombieObject->box.y = 450;
        AddObject(zombieObject);
    }
    LoadAssets();
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
        if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        float mouseX = event.button.x;
        float mouseY = event.button.y;
        for (int i = (int)objectArray.size() - 1; i >= 0; i--) {
            GameObject* go = objectArray[i].get();
            Zombie* zombie = go->GetComponent<Zombie>();

            if (zombie != nullptr && go->box.IsInside(Vec2(mouseX, mouseY))) {
                zombie->Damage(10);   // use o valor de dano do enunciado
                break;
            }
        }
    }
         
    }

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