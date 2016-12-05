#include "../include/EnemyPhysicsComponent.h"

EnemyPhysicsComponent::EnemyPhysicsComponent() {}

void EnemyPhysicsComponent::update(EnemyObject *enemyObj, World *world,
                                   int dt) {

    // platform collision
    if (world->playerIsDead()) {
        return;
    }
    enemyObj->setX(enemyObj->getX() + enemyObj->getXVel() * dt);
    int collide = world->collideWithPlatform(enemyObj).returnResult;
    int collideL = collide & COLLIDE_LEFT;
    int collideR = collide & COLLIDE_RIGHT;

    if (collideR != 0 || collideL != 0) {
        enemyObj->setX(enemyObj->getX() - enemyObj->getXVel() * dt);
        enemyObj->setXVel(-enemyObj->getXVel());
    }

    // also handles trampoline collision
    enemyObj->setY(enemyObj->getY() + enemyObj->getYVel() * dt);
    collide = world->collideWithPlatform(enemyObj).returnResult;
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
