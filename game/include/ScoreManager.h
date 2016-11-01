#ifndef LIZARD_SCORE_MANAGER
#define LIZARD_SCORE_MANAGER

// #include "GameState.h"
#include "PlayerObject.h"
#include "ResourceManager.h"
#include "World.h"
#include <SDL.h>

class ScoreManager {
public:
    ScoreManager(SDL_Renderer *r, ResourceManager *res, World *world,
                 int deaths = 0, int coins = 0);
    int getScore();
    void update();
    void resetScore();
    void printScore(int width, int height);
    void setDeaths(int deaths);
    void setCoins(int coins);

    int getDeaths();
    int getCoins();
    ~ScoreManager();

private:
    int numDeaths = 0;
    int numCoins = 0;
    SDL_Renderer *renderer;
    ResourceManager *resources;
    World *world;
};

#endif
