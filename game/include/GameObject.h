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

    float getX() { return xFloat; }
    float getY() { return yFloat; }
    float getW() { return location.w; }
    float getH() { return location.h; }
    float getXVel() { return xVelocity; }
    float getYVel() { return yVelocity; }

    void setX(float x) { xFloat = x; location.x = x;}
    void setY(float y) { yFloat = y; location.y = y;}
    void setW(int w) { location.w = w; }
    void setH(int h) { location.h = h; }
    void setXVel(float xVel) { xVelocity = xVel; }
    void setYVel(float yVel) { yVelocity = yVel; }

protected:
    float xFloat,yFloat;
    float xVelocity, yVelocity;
    SDL_Rect location;
};

#endif
