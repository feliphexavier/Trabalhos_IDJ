#include "GameObject.h"

GameObject::GameObject() {
    isDead = false;
}

GameObject::~GameObject() {
    for (int i = (int)components.size() - 1; i >= 0; i--) {
        delete *(components.begin() + i);
    }
    components.clear();
}

void GameObject::Update(float dt) {
    for (Component* c : components) {
        c->Update(dt);
    }
}

void GameObject::Render() {
    for (Component* c : components) {
        c->Render();
    }
}

bool GameObject::IsDead() {
    return isDead;
}

void GameObject::RequestDelete() {
    isDead = true;
}

void GameObject::AddComponent(Component* cpt) {
    components.emplace_back(cpt);
}

void GameObject::RemoveComponent(Component* cpt) {
    for (auto it = components.begin(); it != components.end(); ++it) {
        if (*it == cpt) {
            components.erase(it);
            break;
        }
    }
}