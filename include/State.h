#ifndef STATE_H
#define STATE_H

#include <vector>
#include <memory>
#include "Sprite.h"
#include "Music.h"
#include "GameObject.h"
class State{
    public:
    State();
    ~State();
    bool QuitRequested();
    void Update(float dt);
    void LoadAssets();
    void AddObject(GameObject* go);
    void Render();
    private:
    std::vector<std::unique_ptr<GameObject>> objectArray;
    Music music;
    bool quitRequested;
};
#endif