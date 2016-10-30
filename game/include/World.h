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
};

class GameObject;
class World {
public:
    World(int numEntities, int numPlatforms, int numSpikes, int numCheckpoints, int numCoins);

    int transformXtoCamera(int x);
    int transformYtoCamera(int y);

    void updateVolume(int entityNum, int newX, int newY, int newW, int newH);
    bool checkCollisions();

    float getCameraX() { return cameraX; }
    float getCameraY() { return cameraY; }
    int getCameraW() { return camera.w; }
    int getCameraH() { return camera.h; }

    int collideWithPlatform(GameObject *obj);
    bool collideWithSpike(GameObject *obj);
    bool collideWithCheckpoint(GameObject *obj);
    bool collideWithCoin(GameObject *obj);
    bool intersectCamera(SDL_Rect *toTest);

    void setCameraX(float x) {
        cameraX = x;
        camera.x = x;
    }
    void setCameraY(float y) {
        cameraX = y;
        camera.y = y;
    }

    SDL_Rect getEntityLocation(int num);
    SDL_Rect getSpikeLocation(int num);
    SDL_Rect getPlatformLocation(int num);
    SDL_Rect getCheckpointLocation(int num);
    SDL_Rect getCoinLocation(int num);
    int worldXLen = 4 * 1280;
    int worldYLen = 720;
    bool testCollide(SDL_Rect a, SDL_Rect b);
    bool collision = false;
    bool coinCollision = false;

    float getCurrCheckX() { return currCheckX; }
    float getCurrCheckY() { return currCheckY; }

    void setCurrCheckX(float x) { currCheckX = x; }
    void setCurrCheckY(float y) { currCheckY = y; }

    int numEntities, numPlatforms, numSpikes, numCheckpoints, numCoins;

    std::vector<SDL_Rect> entityVolumes;
    std::vector<SDL_Rect> platformVolumes;
    std::vector<SDL_Rect> spikeVolumes;
    std::vector<SDL_Rect> checkpointVolumes;
    std::vector<SDL_Rect> coinVolumes;

private:
    float cameraX = -640.0;
    float cameraY = 0.0;
    float currCheckX = 50;
    float currCheckY = 50;
    SDL_Rect camera = {-640, 0, 1280, 720};
};

#endif
