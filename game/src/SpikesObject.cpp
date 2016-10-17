#include "../include/SpikesObject.h"

SpikesObject::SpikesObject(int x, int y, bool orientation, int spikeNum,
                           SpikesGraphicsComponent *g) {
    location = {x, y, 0, 20};
    this->spikeNum = spikeNum;
    this->xFloat = (float)x;
    this->yFloat = (float)y;
    this->setXVel(0.0);
    this->setYVel(0.0);
    this->setOrientation(orientation);
    this->graphics = g;
    g->setGameObject(this);
    this->location = (g->getTextureRect(g->getCurrentSprite()));
}

SpikesObject::~SpikesObject() {
    delete graphics;

    return;
}
