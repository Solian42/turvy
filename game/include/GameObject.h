#ifndef GAME_OBJECT_LIZARD
#define GAME_OBJECT_LIZARD

#include "World.h"
#include <SDL.h>
class GameObject {

public:
    // Do we need this?
    // void update(World *world, SDL_Renderer *renderer);

    int entityNum;
    SDL_Rect *getLocation() { return &location; }

    int getX() { return location.x; }
    int getY() { return location.y; }
    int getW() { return location.w; }
    int getH() { return location.h; }
    int getXVel() { return xVelocity; }
    int getYVel() { return yVelocity; }

    void setX(int x) { location.x = x; }
    void setY(int y) { location.y = y; }
    void setW(int w) { location.w = w; }
    void setH(int h) { location.h = h; }
    void setXVel(int xVel) { xVelocity = xVel; }
    void setYVel(int yVel) { yVelocity = yVel; }

protected:
    int xVelocity, yVelocity;
    SDL_Rect location;
};

#endif
