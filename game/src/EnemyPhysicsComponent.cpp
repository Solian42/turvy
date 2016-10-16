#include "../include/EnemyPhysicsComponent.h"

EnemyPhysicsComponent::EnemyPhysicsComponent() {}

void EnemyPhysicsComponent::update(EnemyObject *enemyObj, World *world,
                                   int dt) {
    enemyObj->setX(enemyObj->getX() + enemyObj->getXVel() * dt);
    // enemyObj->x += enemyObj->xVelocity;
    enemyObj->setY(enemyObj->getY() + enemyObj->getYVel() * dt);
    // enemyObj->y += enemyObj->yVelocity;
    // If the enemy went too far to the left or right
    if ((enemyObj->getX() < 0) ||
        (enemyObj->getX() + enemyObj->getW() > world->worldXLen)) {
        // Bounce
        enemyObj->setX(enemyObj->getX() - enemyObj->getXVel() * dt);
        enemyObj->setXVel(-enemyObj->getXVel());
        // enemyObj->xVelocity = -enemyObj->xVelocity;
    }

    // If the enemy went too far up or down
    if (enemyObj->getY() < 0.0 ||
        enemyObj->getY() + enemyObj->getH() > world->worldYLen) {

        // Bounce
        enemyObj->setY(enemyObj->getY() - enemyObj->getYVel() * dt);
        enemyObj->setYVel(-enemyObj->getYVel());
        // enemyObj->yVelocity = -enemyObj->yVelocity;
    }

    if ((enemyObj->getY() < 72) && (enemyObj->getX() < 128)) {
        enemyObj->setY(enemyObj->getY() - enemyObj->getYVel() * dt);
        enemyObj->setYVel(-enemyObj->getYVel());
        enemyObj->setX(enemyObj->getX() - enemyObj->getXVel() * dt);
        enemyObj->setXVel(-enemyObj->getXVel());
    }
    world->updateVolume(enemyObj->entityNum, enemyObj->getX(), enemyObj->getY(),
                        enemyObj->getW(), enemyObj->getH());
}

EnemyPhysicsComponent::~EnemyPhysicsComponent() {}
