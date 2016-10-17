#include "../include/PlatformObject.h"

PlatformObject::PlatformObject(int x, int y, int w, int h, int platNum,
                               PlatformGraphicsComponent *g) {
    location = {x, y, w, h};
    this->platNum = platNum;
    this->xFloat = (float)x;
    this->yFloat = (float)y;
    this->setXVel(0.0);
    this->setYVel(0.0);
    this->setW(w);
    this->setH(h);
    this->graphics = g;
    g->setGameObject(this);
}

PlatformObject::~PlatformObject() {
    delete graphics;

    return;
}
