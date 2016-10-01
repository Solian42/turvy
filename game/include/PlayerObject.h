#ifndef PLAYER_OBJECT_LIZARD
#define PLAYER_OBJECT_LIZARD

#include "GameObject.h"
#include "PlayerGraphicsComponent.h"
#include "PlayerInputComponent.h"
#include "PlayerPhysicsComponent.h"
#include "PlayerSoundComponent.h"

class PlayerGraphicsComponent;
class PlayerInputComponent;
class PlayerPhysicsComponent;
class PlayerSoundComponent;

class PlayerObject : public GameObject {

public:
    PlayerObject(int x, int y, int xVelocity, int yVelocity,
                 PlayerInputComponent *i, PlayerGraphicsComponent *g,
                 PlayerSoundComponent *s, PlayerPhysicsComponent *p,
                 int entityNum);

    ~PlayerObject();

    PlayerGraphicsComponent *graphics;
    PlayerInputComponent *input;
    PlayerSoundComponent *sound;
    PlayerPhysicsComponent *physics;
};

#endif
