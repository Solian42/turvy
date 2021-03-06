#ifndef WORLD_LIZARD
#define WORLD_LIZARD
#include "GameObject.h"
#include <SDL.h>
#include <iostream>
#include <vector>
#

enum {
    NO_COLLIDE = 0,
    COLLIDE_LEFT = 1,
    COLLIDE_RIGHT = 2,
    COLLIDE_UP = 4,
    COLLIDE_DOWN = 8,
    COLLIDE_UL = 16,
    COLLIDE_UR = 32,
    COLLIDE_DL = 64,
    COLLIDE_DR = 128
};
typedef struct {
    int returnResult;
    SDL_Rect intersection;
} platCollisionInfo;

class GameObject;
class World {
public:
    World(int width, int height, int numEntities, int numPlatforms,
          int numSpikes, int numCheckpoints, int numCoins, int numTrampolines,
          int numEnemies, int numTeleports, int numDialogues);

    int transformXtoCamera(int x);
    int transformYtoCamera(int y);
    int transformXToWorld(int x);
    int transformYToWorld(int y);

    void updateVolume(int entityNum, int newX, int newY, int newW, int newH);
    bool checkSpikeCollisions();
    bool checkEnemyCollisions();
    bool checkTeleportCollisions();

    float getCameraX() { return cameraX; }
    float getCameraY() { return cameraY; }
    int getCameraW() { return camera.w; }
    int getCameraH() { return camera.h; }

    void setCameraH(int h);

    platCollisionInfo collideWithPlatform(GameObject *obj);
    bool collideWithSpike(GameObject *obj);
    bool collideWithCheckpoint(GameObject *obj);
    std::pair<bool, SDL_Rect> collideWithCoin(GameObject *obj);
    std::pair<bool, SDL_Rect> collideWithTeleport(GameObject *obj);
    bool collideWithTrampoline(GameObject *obj);
    bool collideWithEnemies(GameObject *obj);
    bool intersectCamera(SDL_Rect *toTest);

    void setCameraX(float x) {
        cameraX = x;
        camera.x = x;
    }
    void setCameraY(float y) {
        cameraY = y;
        camera.y = y;
    }

    SDL_Rect getEntityLocation(int num);
    SDL_Rect getSpikeLocation(int num);
    SDL_Rect getPlatformLocation(int num);
    SDL_Rect getCheckpointLocation(int num);
    SDL_Rect getCoinLocation(int num);
    int worldXLen = 0;
    int worldYLen = 0;
    SDL_Rect getTrampolineLocation(int num);
    SDL_Rect getEnemyLocation(int num);
    SDL_Rect getTeleportLocation(int num);
    SDL_Rect getDialogueLocation(int num);
    bool testCollide(SDL_Rect a, SDL_Rect b);
    // bool collision = false;
    void setSpikeCollision(bool collide) { spikeCollision = collide; }
    void setEnemyCollision(bool collide) { enemyCollision = collide; }
    void setCoinCollision(bool collide) { coinCollision = collide; }
    void setTeleportCollision(bool collide) { teleportCollision = collide; }
    void setPlayerDeath(bool death) { isPlayerDead = death; }
    void setPlayerTeleport(bool tele) { isPlayerTeleport = tele; }

    bool isCollidingWithSpike() { return spikeCollision && !godMode; }
    bool isCollidingWithEnemy() { return enemyCollision && !godMode; }
    bool isCollidingWithCoin() { return coinCollision; }
    bool isCollidingWithCheckpoint() { return checkpointCollision; }
    bool isCollidingWithTeleport() { return teleportCollision; }
    bool playerIsDead() { return isPlayerDead; }
    bool playerIsTeleport() { return isPlayerTeleport; }

    bool godMode = false;

    float getCurrCheckX() { return currCheckX; }
    float getCurrCheckY() { return currCheckY; }

    void setCurrCheckX(float x) { currCheckX = x; }
    void setCurrCheckY(float y) { currCheckY = y; }

    float getTeleX() { return teleX; }
    float getTeleY() { return teleY; }

    void setTeleX(float x) { teleX = x; }
    void setTeleY(float y) { teleY = y; }

    int numEntities, numPlatforms, numSpikes, numCheckpoints, numCoins,
        numTrampolines, numEnemies, numTeleports, numDialogues;

    std::vector<SDL_Rect> entityVolumes;
    std::vector<SDL_Rect> platformVolumes;
    std::vector<SDL_Rect> spikeVolumes;
    std::vector<SDL_Rect> checkpointVolumes;
    std::vector<SDL_Rect> coinVolumes;
    std::vector<SDL_Rect> trampolineVolumes;
    std::vector<SDL_Rect> enemyVolumes;
    std::vector<SDL_Rect> teleportVolumes;
    std::vector<SDL_Rect> dialogueVolumes;

private:
    bool checkpointCollision = false;
    bool coinCollision = false;
    bool spikeCollision = false;
    bool enemyCollision = false;
    bool teleportCollision = false;
    bool isPlayerDead = false;
    bool isPlayerTeleport = false;

    float cameraX = -640.0;
    float cameraY = -360.0;
    float currCheckX = 50;
    float currCheckY = 50;
    float teleX = 0;
    float teleY = 0;
    SDL_Rect camera = {-640, -360, 1280, 720};
};

#endif
