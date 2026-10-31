#include "PlayerController.h"
#include "Character.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Camera.h"

PlayerController::PlayerController(GameObject& associated) : Component(associated) {}

void PlayerController::Start() {}
void PlayerController::Render() {}

void PlayerController::Update(float dt) {
    Character* character = associated.GetComponent<Character>();
    if (character == nullptr) return;
    InputManager& input = InputManager::GetInstance();
    float dx = 0, dy = 0;
    if (input.IsKeyDown(SDLK_W)) dy -= 1;
    if (input.IsKeyDown(SDLK_S)) dy += 1;
    if (input.IsKeyDown(SDLK_A)) dx -= 1;
    if (input.IsKeyDown(SDLK_D)) dx += 1;
    if (dx != 0 || dy != 0) {
        character->Issue(Character::Command(Character::Command::MOVE, dx, dy));
    }
    if (input.MousePress(LEFT_MOUSE_BUTTON)) {
        float mx = input.GetMouseX() + Camera::pos.x;
        float my = input.GetMouseY() + Camera::pos.y;
        character->Issue(Character::Command(Character::Command::SHOOT, mx, my));
    }
}