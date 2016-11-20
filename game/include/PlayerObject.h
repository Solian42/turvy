#ifndef PLAYER_OBJECT_LIZARD
#define PLAYER_OBJECT_LIZARD

#include "GameObject.h"
#include "PlayerGraphicsComponent.h"
#include "PlayerInputComponent.h"
#include "PlayerPhysicsComponent.h"
#include "PlayerSoundComponent.h"
#include "ScoreManager.h"

class PlayerGraphicsComponent;
class PlayerInputComponent;
class PlayerPhysicsComponent;
class PlayerSoundComponent;
class ScoreManager;

class PlayerObject : public GameObject {

public:
    PlayerObject(int x, int y, float xVelocity, float yVelocity,
                 PlayerInputComponent *i, PlayerGraphicsComponent *g,
                 PlayerSoundComponent *s, PlayerPhysicsComponent *p,
                 int entityNum, ScoreManager *score);

    ~PlayerObject();

    float getCheckX() { return checkX; }
    float getCheckY() { return checkY; }
    void setCheckX(float x) { checkX = x; }
    void setCheckY(float y) { checkY = y; }

    PlayerGraphicsComponent *graphics;
    PlayerInputComponent *input;
    PlayerSoundComponent *sound;
    PlayerPhysicsComponent *physics;
    ScoreManager *myScore;
    bool onPlatform;
    bool onTrampoline;
    void respawn(World *world);
    void teleport(World *world);

private:
    float checkX = 50;
    float checkY = 50;
};

#endif
