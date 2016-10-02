#include "../include/EnemyObject.h"

EnemyObject::EnemyObject(int x, int y, int xVelocity, int yVelocity,
                         EnemyInputComponent *i, EnemyGraphicsComponent *g,
                         EnemyPhysicsComponent *p, int entityNum) {
    location = {x, y, 0, 0};
    this->xFloat = x;
    this->yFloat = y;
    this->xVelocity = xVelocity;
    this->yVelocity = yVelocity;
    this->input = i;
    this->graphics = g;
    this->physics = p;
    g->GraphicsComponent::setGameObject(this);
    this->location = (g->getTextureRect(g->getCurrentSprite()));
    this->entityNum = entityNum;
}

EnemyObject::~EnemyObject() {
    delete input;
    delete graphics;
    delete physics;
    return;
}
