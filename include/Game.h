#include <string>
#include "State.h"
#include <SDL3/SDL.h>
#include<SDL3_mixer/SDL_mixer.h>

class Game{
    public:
    ~Game();
    void Run();
    SDL_Renderer* GetRenderer();
    State& GetState();
    static Game& GetInstance();
    MIX_Mixer* GetMixer();
    float GetDeltaTime();
    private:
    Game(std::string title, int width, int height);
    std::string title;
    int width;
    int height;
    int frameStart;
    float dt;
    void CalculateDeltaTime();
    static Game* instance;
    SDL_Window* window;
    SDL_Renderer* renderer;
    State* state;

};
