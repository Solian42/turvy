#include "../include/CheckpointObject.h"

CheckpointObject::CheckpointObject(int x, int y, int checkNum,
                               CheckpointGraphicsComponent *g) {
    location = {x, y, 20, 20};
    this->checkNum = checkNum;
    this->xFloat = (float)x;
    this->yFloat = (float)y;
    this->setXVel(0.0);
    this->setYVel(0.0);
    this->graphics = g;
    g->setGameObject(this);
    this->location = (g->getTextureRect(g->getCurrentSprite()));
}

CheckpointObject::~CheckpointObject() {
    delete graphics;

    return;
}