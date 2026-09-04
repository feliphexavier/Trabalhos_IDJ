#include <SDL3/SDL.h>
#include <iostream>
#include "include/Game.h"

int main(int argc, char* argv[]){
    Game::GetInstance().Run();
}