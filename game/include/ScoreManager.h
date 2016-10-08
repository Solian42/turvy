#ifndef LIZARD_SCORE_MANAGER
#define LIZARD_SCORE_MANAGER

// #include "GameState.h"
#include "ResourceManager.h"
#include "World.h"
#include <SDL.h>

class ScoreManager {
public:
    ScoreManager(SDL_Renderer *r, ResourceManager *res, World *world);
    int getScore();
    void update();
    void resetScore();
    void printScore(int width, int height);

    ~ScoreManager();

private:
    int numDeaths = 0;
    SDL_Renderer *renderer;
    ResourceManager *resources;
    World *world;
};

#endif