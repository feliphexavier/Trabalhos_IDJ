#include "Camera.h"
#include "GameObject.h"
#include "InputManager.h"

#define CAMERA_SPEED 300.0f  
#define SCREEN_WIDTH  1200
#define SCREEN_HEIGHT 900

Vec2 Camera::pos(0, 0);
Vec2 Camera::speed(0, 0);
GameObject* Camera::focus = nullptr;

void Camera::Follow(GameObject* newFocus) {
    focus = newFocus;
}

void Camera::Unfollow() {
    focus = nullptr;
}

void Camera::Update(float dt) {
    if (focus != nullptr) {
        pos.x = focus->box.x + focus->box.w / 2 - SCREEN_WIDTH / 2;
        pos.y = focus->box.y + focus->box.h / 2 - SCREEN_HEIGHT / 2;
        return;
    }

    InputManager& input = InputManager::GetInstance();
    speed.x = 0;
    speed.y = 0;

    if (input.IsKeyDown(LEFT_ARROW_KEY))  speed.x -= CAMERA_SPEED;
    if (input.IsKeyDown(RIGHT_ARROW_KEY)) speed.x += CAMERA_SPEED;
    if (input.IsKeyDown(UP_ARROW_KEY))    speed.y -= CAMERA_SPEED;
    if (input.IsKeyDown(DOWN_ARROW_KEY))  speed.y += CAMERA_SPEED;

    pos.x += speed.x * dt;
    pos.y += speed.y * dt;
}