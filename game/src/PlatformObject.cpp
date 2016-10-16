#include "../include/PlatformObject.h"

PlatformObject::PlatformObject(int x, int y, int w, int h,
                               PlatformGraphicsComponent *g) {
    location = {x, y, w, h};
    this->xFloat = (float)x;
    this->yFloat = (float)y;
    this->setW(w);
    this->setH(h);
    this->graphics = g;
    g->setGameObject(this);
    this->location = (g->getTextureRect(g->getCurrentSprite()));
}

PlatformObject::~PlatformObject() {
    delete graphics;

    return;
}