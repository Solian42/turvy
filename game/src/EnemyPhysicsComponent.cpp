#include "../include/EnemyPhysicsComponent.h"

EnemyPhysicsComponent::EnemyPhysicsComponent() {}

void EnemyPhysicsComponent::update(EnemyObject *enemyObj, World *world,
                                   int dt) {

    // enemyObj->x += enemyObj->xVelocity;

    // enemyObj->y += enemyObj->yVelocity;

    // platform collision
    enemyObj->setX(enemyObj->getX() + enemyObj->getXVel() * dt);
    int collide = world->collideWithPlatform(enemyObj);
    int collideL = collide & COLLIDE_LEFT;
    int collideR = collide & COLLIDE_RIGHT;

    if (collideR != 0 || collideL != 0) {
        enemyObj->setX(enemyObj->getX() - enemyObj->getXVel() * dt);
        enemyObj->setXVel(-enemyObj->getXVel());
    }

    enemyObj->setY(enemyObj->getY() + enemyObj->getYVel() * dt);
    collide = world->collideWithPlatform(enemyObj);
    int collideU = collide & COLLIDE_UP;
    int collideD = collide & COLLIDE_DOWN;
    if (collideU != 0 || collideD != 0 ||
        world->collideWithTrampoline(enemyObj)) {
        enemyObj->setY(enemyObj->getY() - enemyObj->getYVel() * dt);
        enemyObj->setYVel(-enemyObj->getYVel());
    }

    world->updateVolume(enemyObj->entityNum, enemyObj->getX(), enemyObj->getY(),
                        enemyObj->getW(), enemyObj->getH());
}

EnemyPhysicsComponent::~EnemyPhysicsComponent() {}
