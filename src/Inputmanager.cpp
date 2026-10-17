#include "InputManager.h"

InputManager& InputManager::GetInstance() {
    static InputManager instance;
    return instance;
}

InputManager::InputManager()
    : quitRequested(false), updateCounter(0), mouseX(0), mouseY(0) {
    for (int i = 0; i < 6; i++) {
        mouseState[i]  = false;
        mouseUpdate[i] = 0;
    }
}
InputManager::~InputManager() {}
void InputManager::Update() {
    float mx, my;
    SDL_GetMouseState(&mx, &my);
    mouseX = static_cast<int>(mx);
    mouseY = static_cast<int>(my);
    quitRequested = false;
    updateCounter++;
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
                quitRequested = true;
                break;
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
            case SDL_EVENT_MOUSE_BUTTON_UP: {
                int button = event.button.button;
                if (button >= 1 && button <= 5) {
                    mouseState[button]  = event.button.down;
                    mouseUpdate[button] = updateCounter;
                }
                break;
            }
            case SDL_EVENT_KEY_DOWN:
            case SDL_EVENT_KEY_UP:
                if (event.key.repeat) break; 
                keyState[event.key.key]  = event.key.down;
                keyUpdate[event.key.key] = updateCounter;
                break;
            default:
                break;
        }
    }
}
bool InputManager::KeyPress(int key)   { return  keyState[key] && keyUpdate[key] == updateCounter; }
bool InputManager::KeyRelease(int key) { return !keyState[key] && keyUpdate[key] == updateCounter; }
bool InputManager::IsKeyDown(int key)  { return  keyState[key]; }
bool InputManager::MousePress(int button)   { return  mouseState[button] && mouseUpdate[button] == updateCounter; }
bool InputManager::MouseRelease(int button) { return !mouseState[button] && mouseUpdate[button] == updateCounter; }
bool InputManager::IsMouseDown(int button)  { return  mouseState[button]; }

int InputManager::GetMouseX() { return mouseX; }
int InputManager::GetMouseY() { return mouseY; }

bool InputManager::QuitRequested() { return quitRequested; }