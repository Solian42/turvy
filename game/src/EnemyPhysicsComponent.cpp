#include "../include/EnemyPhysicsComponent.h"

EnemyPhysicsComponent::EnemyPhysicsComponent() {}

void EnemyPhysicsComponent::update(EnemyObject *enemyObj, World *world) {
    enemyObj->x += enemyObj->xVelocity;
    enemyObj->y += enemyObj->yVelocity;
    // If the enemy went too far to the left or right
    if ((enemyObj->x < 0) ||
        (enemyObj->x + enemyObj->enemySpriteW > world->x)) {
        // Bounce
        enemyObj->xVelocity = -enemyObj->xVelocity;
    }

    // If the enemy went too far up or down
    if (enemyObj->y - enemyObj->enemySpriteH < 0 || enemyObj->y > world->y) {

        // Bounce
        enemyObj->yVelocity = -enemyObj->yVelocity;
    }

    world->updateVolume(enemyObj->entityNum, enemyObj->x, enemyObj->y,
                        enemyObj->enemySpriteW, enemyObj->enemySpriteH);
}

EnemyPhysicsComponent::~EnemyPhysicsComponent() {}
