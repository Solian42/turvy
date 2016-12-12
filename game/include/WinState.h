#ifndef LIZARD_WIN_STATE
#define LIZARD_WIN_STATE

#include "State.h"

class WinState : public State {
public:
    int getMyState() { return STATE_WIN; }
    WinState(SDL_Renderer *r, int width, int height,
                        ResourceManager *res);
    int handleEvent(SDL_Event *e, int dt);
    void doSound();
    void doPhysics(int dt);
    void render(int dt);
    void startMusic(int vol);

    ~WinState();

private:
    int width, height;
    int time = 0;

    SDL_Texture *title = nullptr;
    SDL_Rect titleRect;

    int titleAlpha = 0;
    bool fadein = false;
    SDL_Renderer *renderer;
    ResourceManager *resources;

    void floatingMove(int speed, int dt);
};

#endif
