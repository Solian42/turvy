#ifndef LIZARD_TITLE_STATE
#define LIZARD_TITLE_STATE

#include "State.h"

class TitleState : public State {
public:
    int getMyState() { return STATE_TITLE; }
    TitleState(SDL_Renderer *r, int width, int height, ResourceManager *res);
    int handleEvent(SDL_Event *e, int dt);
    void doSound();
    void doPhysics(int dt);
    void render(int dt);
    void startMusic(int vol);

    ~TitleState();

private:
    int width, height;
    int time = 0;

    SDL_Texture *splash = nullptr;
    SDL_Rect splashRect;

    int splashAlpha = 0;
    bool fadein = false;
    SDL_Renderer *renderer;
    ResourceManager *resources;
};

#endif
