#include "../include/PlayerObject.h"

PlayerObject::PlayerObject(int x, int y, int xVelocity, int yVelocity,
                           PlayerInputComponent *i, PlayerGraphicsComponent *g,
                           PlayerSoundComponent *s, PlayerPhysicsComponent *p,
                           int entityNum) {
    this->x = x;
    this->y = y;
    this->xVelocity = xVelocity;
    this->yVelocity = yVelocity;
    this->input = i;
    this->graphics = g;
    this->sound = s;
    this->physics = p;
    playerSpriteW = g->getTextureW();
    playerSpriteH = g->getTextureH();

    this->entityNum = entityNum;
}

PlayerObject::~PlayerObject() {}
