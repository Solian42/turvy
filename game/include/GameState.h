#ifndef LIZARD_GAME_STATE
#define LIZARD_GAME_STATE

#include "EnemyObject.h"
#include "PlayerObject.h"
#include "State.h"
#include "World.h"

class GameState : public State {
public:
    const int STATETYPE = STATE_GAME;
    GameState(SDL_Renderer *r, int width, int height, ResourceManager *res);
    int handleEvent(SDL_Event *e, int dt);
    void doSound();
    void doPhysics(int dt);
    void render(int dt);
    void startMusic();

    ~GameState();

private:
    int numEntities;

    std::vector<GameObject *> entities;
    std::string backgroundMusic;
    PlayerObject *player;
    std::vector<EnemyObject *> enemies;

    SDL_Renderer *renderer;
    World *world;

    PlayerObject *createPlayer(int entityNum,
                               std::vector<std::string> spriteNames);
    EnemyObject *createEnemy(int x, int y, int entityNum,
                             std::vector<std::string> spriteNames);
};

#endif
