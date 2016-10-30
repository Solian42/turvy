#ifndef COIN_OBJECT_LIZARD
#define COIN_OBJECT_LIZARD

#include "CoinGraphicsComponent.h"
#include "CoinPhysicsComponent.h"
#include "GameObject.h"
#include "PlayerObject.h"

class CoinGraphicsComponent;
class CoinPhysicsComponent;
class PlayerObject;

class CoinObject : public GameObject {

public:
    CoinObject(int x, int y, int checkNum, CoinGraphicsComponent *g,
               CoinPhysicsComponent *p, PlayerObject *pl);

    ~CoinObject();

    CoinGraphicsComponent *graphics;
    CoinPhysicsComponent *physics;
    PlayerObject *playerObj;
    int checkNum;
    bool isEaten = false;

private:
};

#endif