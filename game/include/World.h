#ifndef WORLD_LIZARD
#define WORLD_LIZARD
#include "GameObject.h"
#include <SDL.h>
#include <iostream>
#include <vector>

enum {
    NO_COLLIDE = -1,
    COLLIDE_LEFT = 0,
    COLLIDE_RIGHT = 1,
    COLLIDE_UP = 2,
    COLLIDE_DOWN = 3,
};

class GameObject;
class World {
public:
    World(int numEntities);

    int transformXtoCamera(int x);
    int transformYtoCamera(int y);

    void updateVolume(int entityNum, int newX, int newY, int newW, int newH);
    bool checkCollisions();

    float getCameraX() { return cameraX; }
    float getCameraY() { return cameraY; }
    int getCameraW() { return camera.w; }
    int getCameraH() { return camera.h; }

    int collideWithPlatform(GameObject *obj);

    void setCameraX(float x) {
        cameraX = x;
        camera.x = x;
    }
    void setCameraY(float y) {
        cameraX = y;
        camera.y = y;
    }

    SDL_Rect getEntityLocation(int num);
    int worldXLen = 1280;
    int worldYLen = 720;
    bool testCollide(SDL_Rect a, SDL_Rect b);
    bool collision = false;

    int numEntities;

private:
    float cameraX = -640.0;
    float cameraY = 0.0;
    SDL_Rect camera = {-640, 0, 1280, 720};
    std::vector<SDL_Rect> entityVolumes;
    std::vector<SDL_Rect> platformVolumes;
};

#endif
