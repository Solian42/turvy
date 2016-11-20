#include "../include/TeleportObject.h"

TeleportObject::TeleportObject(int x, int y, int newX, int newY, int checkNum,
                               TeleportGraphicsComponent *g,
                               TeleportPhysicsComponent *p, PlayerObject *pl) {
    location = {x, y, 40, 40};
    this->checkNum = checkNum;
    this->xFloat = (float)x;
    this->yFloat = (float)y;
    this->newXFloat = (float)newX;
    this->newYFloat = (float)newY;
    this->setXVel(0.0);
    this->setYVel(0.0);
    this->graphics = g;
    this->physics = p;
    this->playerObj = pl;
    g->setGameObject(this);
}

TeleportObject::~TeleportObject() {
    delete graphics;
    delete physics;
    return;
}
