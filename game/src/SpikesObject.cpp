#include "../include/SpikesObject.h"

SpikesObject::SpikesObject(int x, int y, int orientation, int spikeNum,
                           SpikesGraphicsComponent *g) {
    location = {x, y, 20, 20};
    this->spikeNum = spikeNum;
    this->xFloat = (float)x;
    this->yFloat = (float)y;
    this->setXVel(0.0);
    this->setYVel(0.0);
    this->setOrientation(orientation);
    this->graphics = g;
    g->setGameObject(this);
    this->location = {x, y, 20, 20};
}

SpikesObject::~SpikesObject() {
    delete graphics;

    return;
}
