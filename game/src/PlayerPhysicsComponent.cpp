#include "../include/PlayerPhysicsComponent.h"

PlayerPhysicsComponent::PlayerPhysicsComponent() {}

void PlayerPhysicsComponent::update(PlayerObject *playerObj, World *world,
                                    int dt) {
    playerObj->setX(playerObj->getX() + playerObj->getXVel() * dt);
    world->setCameraX((world->getCameraX() + playerObj->getXVel() * dt));

    int collide = world->collideWithPlatform(playerObj);
    int collideL = collide & COLLIDE_LEFT;
    int collideR = collide & COLLIDE_RIGHT;

    if (collideR != 0 || collideL != 0) {
        playerObj->setX(playerObj->getX() - playerObj->getXVel() * dt);
        world->setCameraX((world->getCameraX() - playerObj->getXVel() * dt));
    }

    playerObj->setY(playerObj->getY() + playerObj->getYVel() * dt);

    world->setCameraY((world->getCameraY() + playerObj->getYVel() * dt));

    collide = world->collideWithPlatform(playerObj);
    int collideU = collide & COLLIDE_UP;
    int collideD = collide & COLLIDE_DOWN;
    if (collideU != 0 || collideD != 0) {
        playerObj->setY(playerObj->getY() - playerObj->getYVel() * dt);
        world->setCameraY((world->getCameraY() - playerObj->getYVel() * dt));
        if (playerObj->onTrampoline) {
            playerObj->onTrampoline = false;
            if (playerObj->graphics->isUpsideDown()) {
                playerObj->graphics->setUpsideDown(false);
            } else {
                playerObj->graphics->setUpsideDown(true);
            }
        }
        playerObj->onPlatform = true;
    }
    if (collide == NO_COLLIDE) {
        playerObj->onPlatform = false;
    }
    world->updateVolume(playerObj->entityNum, playerObj->getX(),
                        playerObj->getY(), playerObj->getW(),
                        playerObj->getH());
    // if we got hit by a spike
    if (world->collideWithSpike(playerObj)) {
        playerObj->setX(playerObj->getCheckX());

        world->setCameraX(-640 + playerObj->getCheckX());
        world->setCameraY(playerObj->getCheckY() - 360);
        playerObj->setY(playerObj->getCheckY());
        // no need to set the x velocity
        playerObj->setYVel(-.5);
        playerObj->graphics->setUpsideDown(false);
        playerObj->graphics->setCurrState(0);
        world->updateVolume(playerObj->entityNum, playerObj->getX(),
                            playerObj->getY(), playerObj->getW(),
                            playerObj->getH());
    }

    // if we collide with an enemy
    if (world->collideWithEnemies(playerObj)) {
        playerObj->setX(playerObj->getCheckX());
        world->setCameraX(-640 + playerObj->getCheckX());
        playerObj->setY(playerObj->getCheckY());
        world->setCameraY(playerObj->getCheckY() - 360);
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
        if (world->getCurrCheckX() != playerObj->getCheckX() &&
            world->getCurrCheckY() != playerObj->getCheckY()) {
            playerObj->sound->playSound("cp");
        }
        playerObj->setCheckX(world->getCurrCheckX());
        playerObj->setCheckY(world->getCurrCheckY());
    }

    if (world->collideWithTrampoline(playerObj)) {
        playerObj->onPlatform = false;
        if (playerObj->graphics->isUpsideDown()) {
            playerObj->sound->playSound("jump2");
            playerObj->graphics->setUpsideDown(false);
            playerObj->setY(playerObj->getY() - playerObj->getYVel() * dt);
            world->setCameraY(
                (world->getCameraY() - playerObj->getYVel() * dt));
            playerObj->setYVel(.5);
        } else {
            playerObj->sound->playSound("jump");
            playerObj->graphics->setUpsideDown(true);
            playerObj->setY(playerObj->getY() - playerObj->getYVel() * dt);
            world->setCameraY(
                (world->getCameraY() - playerObj->getYVel() * dt));
            playerObj->setYVel(-.5);
        }
        playerObj->onTrampoline = true;
    } else {
        playerObj->onTrampoline = false;
    }
}

PlayerPhysicsComponent::~PlayerPhysicsComponent() {}
