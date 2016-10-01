#include "../include/PlayerPhysicsComponent.h"

PlayerPhysicsComponent::PlayerPhysicsComponent() {}

void PlayerPhysicsComponent::update(PlayerObject *playerObj, World *world,
                                    int dt) {
    playerObj->setX(playerObj->getX() + playerObj->getXVel() * dt);
    // playerObj->x += playerObj->xVelocity;
    playerObj->setY(playerObj->getY() + playerObj->getYVel() * dt);
    // playerObj->y += playerObj->yVelocity;
    // If the player went too far to the left or right
    if ((playerObj->getX() < 0) ||
        (playerObj->getX() + playerObj->getW() > world->x)) {
        // Move back
        playerObj->setX(playerObj->getX() - playerObj->getXVel() * dt);
        // playerObj->x -= playerObj->xVelocity;
    }

    // If the player went too far up or down
    if (playerObj->getY() - playerObj->getH() < 0 ||
        (playerObj->getY() > world->y)) {
        // Move back
        playerObj->setY(playerObj->getY() - playerObj->getYVel() * dt);
        // playerObj->y -= playerObj->yVelocity;
    }

    world->updateVolume(playerObj->entityNum, playerObj->getX(),
                        playerObj->getY(), playerObj->getW(),
                        playerObj->getH());
}

PlayerPhysicsComponent::~PlayerPhysicsComponent() {}
