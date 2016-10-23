#ifndef LIZARD_LEVELONEBEGIN_STATE
#define LIZARD_LEVELONEBEGIN_STATE

#include "State.h"

class LevelOneBeginState : public State {
public:
    int getMyState() { return STATE_LEVELONEBEGIN; }
    LevelOneBeginState(SDL_Renderer *r, int width, int height, ResourceManager *res);
    int handleEvent(SDL_Event *e, int dt);
    void doSound();
    void doPhysics(int dt);
    void render(int dt);
    void startMusic(int vol);

    ~LevelOneBeginState();

private:
    int width, height;
    int time = 0;

    SDL_Texture *title = nullptr;
    SDL_Rect titleRect;

    SDL_Texture *ready = nullptr;
    SDL_Rect readyRect;

    std::string titleTitle = "LEVEL ONE";
    std::string readyTitle = "[Press space to start level one!]";
    int titleAlpha = 0;
    bool fadein = false;
    SDL_Renderer *renderer;
    ResourceManager *resources;

    void floatingMove(int speed, int dt);
};

#endif