#include "../include/DialogueObject.h"

DialogueObject::DialogueObject(int x, int y, int w, int h, int checkNum,
                               DialogueGraphicsComponent *g,
                               DialogueInputComponent *i) {
    location = {x, y, w, h};
    this->checkNum = checkNum;
    this->xFloat = (float)x;
    this->yFloat = (float)y;
    this->setXVel(0.0);
    this->setYVel(0.0);
    this->setW(w);
    this->setH(h);
    this->graphics = g;
    this->input = i;
    g->setGameObject(this);
}

DialogueObject::~DialogueObject() {
    delete graphics;
    delete input;
    return;
}
