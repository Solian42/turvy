#ifndef WORLD_LIZARD
#define WORLD_LIZARD
#include <SDL.h>
#include <iostream>
#include <vector>
class World {
public:
    World(int numEntities);

    int transformX(int x);
    int transformY(int y);

    void updateVolume(int entityNum, int newX, int newY, int newW, int newH);
    bool checkCollisions();

    SDL_Rect getEntityLocation(int num);
    int x = 1280;
    int y = 720;

    bool collision = false;

    int numEntities;

private:
    bool testCollide(SDL_Rect a, SDL_Rect b);
    std::vector<SDL_Rect> entityVolumes;
};

#endif
