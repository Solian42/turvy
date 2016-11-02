#include "../include/TrampolineObject.h"

TrampolineObject::TrampolineObject(int x, int y, int trampolineNum,
                           TrampolineGraphicsComponent *g) {
    location = {x, y, 10, 10};
    this->trampolineNum = trampolineNum;
    this->xFloat = (float)x;
    this->yFloat = (float)y;
    this->setXVel(0.0);
    this->setYVel(0.0);
    this->graphics = g;
    g->setGameObject(this);
    this->location = {x, y, 10, 10};
}

TrampolineObject::~TrampolineObject() {
    delete graphics;

    return;
}
