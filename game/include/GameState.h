#ifndef LIZARD_GAME_STATE
#define LIZARD_GAME_STATE

#include "EnemyObject.h"
#include "PlayerObject.h"
#include "ScoreManager.h"
#include "State.h"
#include "World.h"

class GameState : public State {
public:
    int getMyState() { return STATE_GAME; }
    GameState(SDL_Renderer *r, int width, int height, ResourceManager *res);
    int handleEvent(SDL_Event *e, int dt);
    int getHighScore();

    void reset();
    void doSound();
    void doPhysics(int dt);
    void render(int dt);
    void startMusic();

    ~GameState();

private:
    int numEntities;

    std::vector<GameObject *> entities;
    std::vector<GameObject *> backgroundObjects;
    std::string backgroundMusic;
    PlayerObject *player = nullptr;
    std::vector<EnemyObject *> enemies;

    SDL_Renderer *renderer;
    World *world = nullptr;

    bool hasWon = false;

    PlayerObject *createPlayer(int entityNum,
                               std::vector<std::string> spriteNames);
    EnemyObject *createEnemy(int x, int y, int entityNum,
                             std::vector<std::string> spriteNames);
    GameObject *createSetpiece(int x, int y, std::vector<std::string> sprites);

    ScoreManager *scoreMgr = nullptr;
};

#endif
