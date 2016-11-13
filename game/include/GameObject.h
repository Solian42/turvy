#ifndef GAME_OBJECT_LIZARD
#define GAME_OBJECT_LIZARD

#include "GraphicsComponent.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "SoundComponent.h"
#include "World.h"
#include <SDL.h>

class GraphicsComponent;
class SoundComponent;
class InputComponent;
class PhysicsComponent;

class GameObject {

public:

    int entityNum;
    SDL_Rect *getLocation() { return &location; }

    float getX() { return xFloat; }
    float getY() { return yFloat; }
    float getW() { return location.w; }
    float getH() { return location.h; }
    float getXVel() { return xVelocity; }
    float getYVel() { return yVelocity; }

    void setX(float x) {
        xFloat = x;
        location.x = x;
    }
    void setY(float y) {
        yFloat = y;
        location.y = y;
    }
    void setW(int w) { location.w = w; }
    void setH(int h) { location.h = h; }
    void setXVel(float xVel) { xVelocity = xVel; }
    void setYVel(float yVel) { yVelocity = yVel; }

    GraphicsComponent *graphics = nullptr;
    SoundComponent *sound = nullptr;
    InputComponent *input = nullptr;
    PhysicsComponent *physics = nullptr;

protected:
    float xFloat, yFloat;
    float xVelocity, yVelocity;
    SDL_Rect location;
};

#endif
