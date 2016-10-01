#ifndef STATE_LIZARD
#define STATE_LIZARD

#include "ResourceManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>

enum {
    STATE_TITLE = 0,
    STATE_MAINMENU = 1,
    STATE_GAME = 2,
    STATE_HIGHSCORE = 3,
};

class State {

public:
	int getMyState();
    virtual int handleEvent(SDL_Event *e, int dt) = 0;
    virtual void doPhysics(int dt) = 0;
    virtual void doSound() = 0;
    virtual void render(int dt) = 0;
    virtual void startMusic() = 0;

protected:
    ResourceManager *resources;
};

#endif
