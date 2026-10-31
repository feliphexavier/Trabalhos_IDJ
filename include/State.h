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
    void Render();
    void Start();
    std::weak_ptr<GameObject> AddObject(GameObject* go);
    std::weak_ptr<GameObject> GetObjectPtr(GameObject* go);
    private:
    bool started;
    std::vector<std::shared_ptr<GameObject>> objectArray; 
    Music music;
    bool quitRequested;
};
#endif