#include "../include/EnemyObject.h"

EnemyObject::EnemyObject(int x, int y, int xVelocity, int yVelocity,
                         EnemyInputComponent *i, EnemyGraphicsComponent *g,
                         EnemyPhysicsComponent *p, int entityNum) {
    this->x = x;
    this->y = y;
    this->xVelocity = xVelocity;
    this->yVelocity = yVelocity;
    this->input = i;
    this->graphics = g;
    this->physics = p;
    enemySpriteW = g->getTextureW();
    enemySpriteH = g->getTextureH();

    this->entityNum = entityNum;
}

EnemyObject::~EnemyObject() {}
