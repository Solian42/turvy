#include "../include/EnemyObject.h"

EnemyObject::EnemyObject(int x, int y, int direction, EnemyInputComponent *i,
                         EnemyGraphicsComponent *g, EnemyPhysicsComponent *p,
                         int entityNum) {
    location = {x, y, 25, 25};
    this->xFloat = (float)x;
    this->yFloat = (float)y;
    this->direction = direction;
    this->input = i;
    this->input->update(this);
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
