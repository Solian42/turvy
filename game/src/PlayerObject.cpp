#include "../include/PlayerObject.h"

PlayerObject::PlayerObject(int x, int y, int xVelocity, int yVelocity,
                           PlayerInputComponent *i, PlayerGraphicsComponent *g,
                           PlayerSoundComponent *s, PlayerPhysicsComponent *p,
                           int entityNum) {
    location = {x, y, 0, 0};
    this->xVelocity = xVelocity;
    this->yVelocity = yVelocity;
    this->input = i;
    this->graphics = g;
    this->sound = s;
    this->physics = p;
    g->setGameObject(this);
    this->location = (g->getTextureRect(g->getCurrentSprite()));
    this->entityNum = entityNum;
}

PlayerObject::~PlayerObject() {
    delete graphics;
    delete input;
    delete sound;
    delete physics;

    return;
}
