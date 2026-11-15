#include "AIController.h"
#include "Character.h"
#include "GameObject.h"

int AIController::npcCounter = 0;

AIController::AIController(GameObject& associated)
    : Component(associated), state(RESTING), destination(0, 0) {
    npcCounter++;
}

AIController::~AIController() {
    npcCounter--;
}

void AIController::Render() {}

void AIController::Update(float dt) {
    Character* self = associated.GetComponent<Character>();
    if (self == nullptr || self->IsDead()) return;

    if (Character::player == nullptr || Character::player->IsDead()) return;

    if (state == RESTING) {
        restTimer.Update(dt);
        if (restTimer.Get() > 1.5f) {
            destination = Character::player->GetCenter();   
            state = MOVING;
        }
    } else {   
        Vec2 me = self->GetCenter();
        Vec2 dir = destination - me;

        if (dir.Magnitude() > 20) {
            self->Issue(Character::Command(Character::Command::MOVE, dir.x, dir.y));
        } else {
            Vec2 target = Character::player->GetCenter();
            self->Issue(Character::Command(Character::Command::SHOOT, target.x, target.y));
            restTimer.Restart();
            state = RESTING;
        }
    }
}