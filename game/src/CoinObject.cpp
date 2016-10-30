#include "../include/CoinObject.h"

CoinObject::CoinObject(int x, int y, int checkNum, CoinGraphicsComponent *g,
                       CoinPhysicsComponent *p, PlayerObject *pl) {
    location = {x, y, 40, 40};
    this->checkNum = checkNum;
    this->xFloat = (float)x;
    this->yFloat = (float)y;
    this->setXVel(0.0);
    this->setYVel(0.0);
    this->graphics = g;
    this->physics = p;
    this->playerObj = pl;
    g->setGameObject(this);
}

CoinObject::~CoinObject() {
    delete graphics;
    delete physics;
    return;
}
