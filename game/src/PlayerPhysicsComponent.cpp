#include "../include/PlayerPhysicsComponent.h"

PlayerPhysicsComponent::PlayerPhysicsComponent() {}

void PlayerPhysicsComponent::update(PlayerObject *playerObj, World *world,
                                    int dt) {
    playerObj->setX(playerObj->getX() + playerObj->getXVel() * dt);
    world->setCameraX((world->getCameraX() + playerObj->getXVel() * dt));

    switch (world->collideWithPlatform(playerObj)) {
    case COLLIDE_LEFT:
        playerObj->setX(playerObj->getX() - playerObj->getXVel() * dt);
        world->setCameraX((world->getCameraX() - playerObj->getXVel() * dt));
        break;
    case COLLIDE_RIGHT:
        playerObj->setX(playerObj->getX() - playerObj->getXVel() * dt);
        world->setCameraX((world->getCameraX() - playerObj->getXVel() * dt));
        break;
    case NO_COLLIDE:
        playerObj->onPlatform = false;
        break;
    }

    // playerObj->x += playerObj->xVelocity;
    playerObj->setY(playerObj->getY() + playerObj->getYVel() * dt);
    // playerObj->y += playerObj->yVelocity;
    switch (world->collideWithPlatform(playerObj)) {
    case COLLIDE_UP:
        playerObj->setY(playerObj->getY() - playerObj->getYVel() * dt);
        playerObj->onPlatform = true;
        break;
    case COLLIDE_DOWN:
        playerObj->setY(playerObj->getY() - playerObj->getYVel() * dt);
        playerObj->onPlatform = true;
        break;
    case NO_COLLIDE:
        playerObj->onPlatform = false;
        break;
    }
    world->updateVolume(playerObj->entityNum, playerObj->getX(),
                        playerObj->getY(), playerObj->getW(),
                        playerObj->getH());
    // if we got hit by an enemy
    if (world->collideWithSpike(playerObj)) {
        playerObj->setX(50);
        world->setCameraX(-640 + 50);
        playerObj->setY(50);
        // no need to set the x velocity
        playerObj->setYVel(-.5);
        playerObj->graphics->setUpsideDown(false);
        playerObj->graphics->setCurrState(0);
        world->updateVolume(playerObj->entityNum, playerObj->getX(),
                            playerObj->getY(), playerObj->getW(),
                            playerObj->getH());
    }
}

PlayerPhysicsComponent::~PlayerPhysicsComponent() {}
