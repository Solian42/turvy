#include "../include/PlayerPhysicsComponent.h"

PlayerPhysicsComponent::PlayerPhysicsComponent() {}

void PlayerPhysicsComponent::update(PlayerObject *playerObj, World *world,
                                    int dt) {
    playerObj->setX(playerObj->getX() + playerObj->getXVel() * dt);
    world->setCameraX((world->getCameraX() + playerObj->getXVel() * dt));
    // playerObj->x += playerObj->xVelocity;
    playerObj->setY(playerObj->getY() + playerObj->getYVel() * dt);
    // playerObj->y += playerObj->yVelocity;
    // If the player went too far to the left or right
    if ((playerObj->getX() < 0.0) ||
        (playerObj->getX() + playerObj->getW() > world->worldXLen)) {
        // Move back
        playerObj->setX(playerObj->getX() - playerObj->getXVel() * dt);
        world->setCameraX((world->getCameraX() - playerObj->getXVel() * dt));
        // playerObj->x -= playerObj->xVelocity;
    }

    switch (world->collideWithPlatform(playerObj)) {
    case COLLIDE_LEFT:
        playerObj->setX(playerObj->getX() - playerObj->getXVel() * dt);
        world->setCameraX((world->getCameraX() - playerObj->getXVel() * dt));
        break;
    case COLLIDE_RIGHT:
        playerObj->setX(playerObj->getX() - playerObj->getXVel() * dt);
        world->setCameraX((world->getCameraX() - playerObj->getXVel() * dt));
        break;
    case COLLIDE_UP:

        break;
    case COLLIDE_DOWN:
        break;
    case NO_COLLIDE:
        break;
    }

    // If the player went too far up or down
    if (playerObj->getY() < 0.0) {
        // move back
        playerObj->setY(playerObj->getY() - playerObj->getYVel() * dt);
        playerObj->setYVel(0.0);
        if (playerObj->getYVel() != 0.0) {
            playerObj->setYVel(0.0);
        }

    } else if (playerObj->getY() + playerObj->getH() >= world->worldYLen) {
        // Move back
        playerObj->setY(playerObj->getY() - playerObj->getYVel() * dt);
        playerObj->setYVel(0.0);
        if (playerObj->getYVel() != 0.0) {
            playerObj->setYVel(0.0);
        }
        // playerObj->y -= playerObj->yVelocity;
    }

    world->updateVolume(playerObj->entityNum, playerObj->getX(),
                        playerObj->getY(), playerObj->getW(),
                        playerObj->getH());

    // if we got hit by an enemy
    if (world->collision) {
        playerObj->setX(0);
        world->setCameraX(-640);
        playerObj->setY(0);
        // no need to set the x velocity
        playerObj->setYVel(0);
        playerObj->graphics->setUpsideDown(false);
        playerObj->graphics->setCurrState(0);
        world->updateVolume(playerObj->entityNum, playerObj->getX(),
                            playerObj->getY(), playerObj->getW(),
                            playerObj->getH());
    }
}

PlayerPhysicsComponent::~PlayerPhysicsComponent() {}
