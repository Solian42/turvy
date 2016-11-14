#ifndef LIZARD_GAME_STATE
#define LIZARD_GAME_STATE

#include "EnemyObject.h"
#include "PlayerObject.h"
#include "ScoreManager.h"
#include "State.h"
#include "World.h"
#include "XmlParser.h"

class GameState : public State {
public:
    int getMyState() { return STATE_GAME; }
    GameState(SDL_Renderer *r, int width, int height, ResourceManager *res,
              std::vector<std::vector<std::string>> levelData, int levels);
    int handleEvent(SDL_Event *e, int dt);
    int getHighScore();

    void reset();
    void doSound();
    void doPhysics(int dt);
    void render(int dt);
    void startMusic(int vol);

    ~GameState();

private:
    int numLevels;
    int currLevel = 0;
    int numEntities;
    int numDeaths = 0;
    int numCoins = 0;
    int numTrampolines = 0;
    int numEnemies = 0;
    int windowHeight, windowWidth;
    const int MIN_TILE_SIZE = 10;
    std::vector<GameObject *> entities;
    std::vector<GameObject *> backgroundObjects;
    std::vector<PlatformObject *> platforms;
    std::vector<SpikesObject *> spikes;
    std::vector<CheckpointObject *> checkpoints;
    std::vector<CoinObject *> coins;
    std::vector<TrampolineObject *> trampolines;
    std::vector<EnemyObject *> enemies;
    std::string backgroundMusic;
    PlayerObject *player = nullptr;

    std::vector<std::string> levelNames;
    std::vector<std::string> levelMusic;
    std::vector<std::string> backgrounds;

    SDL_Renderer *renderer;
    World *world = nullptr;

    SDL_Texture *background = nullptr;
    SDL_Texture *statics = nullptr;
    bool hasWon = false;

    void loadNewLevel(std::string levelName);
    void cleanCurrentLevel();

    PlayerObject *createPlayer(int entityNum, ScoreManager *score,
                               std::vector<std::string> spriteNames);
    EnemyObject *createEnemy(int x, int y, int entityNum,
                             std::vector<std::string> spriteNames);
    GameObject *createSetpiece(int x, int y, std::vector<std::string> sprites);

    ScoreManager *scoreMgr = nullptr;
};

#endif
