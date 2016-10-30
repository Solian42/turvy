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
    // if we got hit by a spike
    if (world->collideWithSpike(playerObj)) {
        playerObj->setX(playerObj->getCheckX());
        world->setCameraX(-640 + playerObj->getCheckX());
        playerObj->setY(playerObj->getCheckY());
        // no need to set the x velocity
        playerObj->setYVel(-.5);
        playerObj->graphics->setUpsideDown(false);
        playerObj->graphics->setCurrState(0);
        world->updateVolume(playerObj->entityNum, playerObj->getX(),
                            playerObj->getY(), playerObj->getW(),
                            playerObj->getH());
    }

    // if we collide with a checkpoint
    if (world->collideWithCheckpoint(playerObj)) {
        playerObj->setCheckX(world->getCurrCheckX());
        playerObj->setCheckY(world->getCurrCheckY());
    }

    if (world->getCameraX() != (playerObj->getX() - (640))) {
        std::cout << "Houston we have a problem\n";
    }
}

PlayerPhysicsComponent::~PlayerPhysicsComponent() {}
