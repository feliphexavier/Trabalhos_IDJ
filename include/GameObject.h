#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include "Rect.h"
#include "Component.h"

class GameObject {
public:
    GameObject();
    ~GameObject();
    void Update(float dt);
    void Render();
    bool IsDead();
    void RequestDelete();
    void AddComponent(Component* cpt);
    void RemoveComponent(Component* cpt);
    template <typename T>
    T* GetComponent();
    Rect box;
private:
    std::vector<Component*> components;
    bool isDead;
};

template <typename T>
T* GameObject::GetComponent() {
    for (Component* c : components) {
        T* casted = dynamic_cast<T*>(c);
        if (casted != nullptr) {
            return casted;
        }
    }
    return nullptr;
}

#endif