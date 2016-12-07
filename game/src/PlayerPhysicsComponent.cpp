#include "../include/PlayerPhysicsComponent.h"

PlayerPhysicsComponent::PlayerPhysicsComponent() {}

void PlayerPhysicsComponent::update(PlayerObject *playerObj, World *world,
                                    int dt) {
    if (world->playerIsDead()) {
        return;
    }
    platCollisionInfo pcInfo = world->collideWithPlatform(playerObj);
    int collide = pcInfo.returnResult;
    SDL_Rect colRect = pcInfo.intersection;

    if (collide > 8) {
        // if(collide & COLLIDE_UR){
        playerObj->setX(playerObj->getX() - playerObj->getXVel() * dt);
        world->setCameraX((world->getCameraX() - playerObj->getXVel() * dt));
        playerObj->setY(playerObj->getY() - playerObj->getYVel() * dt);
        world->setCameraY((world->getCameraY() - playerObj->getYVel() * dt));
        // }
    } else {
        playerObj->setX(playerObj->getX() + playerObj->getXVel() * dt);
        world->setCameraX((world->getCameraX() + playerObj->getXVel() * dt));

        collide = world->collideWithPlatform(playerObj).returnResult;
        int collideL = collide & COLLIDE_LEFT;
        int collideR = collide & COLLIDE_RIGHT;

        if (collideR != 0 || collideL != 0) {
            playerObj->setX(playerObj->getX() - playerObj->getXVel() * dt);
            world->setCameraX(
                (world->getCameraX() - playerObj->getXVel() * dt));
        }

        playerObj->setY(playerObj->getY() + playerObj->getYVel() * dt);
        world->setCameraY((world->getCameraY() + playerObj->getYVel() * dt));

        collide = world->collideWithPlatform(playerObj).returnResult;
        int collideU = collide & COLLIDE_UP;
        int collideD = collide & COLLIDE_DOWN;
        if (collideU != 0 || collideD != 0) {
            playerObj->setY(playerObj->getY() - playerObj->getYVel() * dt);
            world->setCameraY(
                (world->getCameraY() - playerObj->getYVel() * dt));
            playerObj->onPlatform = true;
        }
    }

    if (collide == NO_COLLIDE) {
        playerObj->onPlatform = false;
    }
    pcInfo = world->collideWithPlatform(playerObj);
    collide = pcInfo.returnResult;
    colRect = pcInfo.intersection;
    if (colRect.w > 0 && colRect.h > 0) {
        // printf("colRect: { %d, %d, %d, %d}", colRect.x, colRect.y, colRect.w,
        // colRect.h);
        switch (collide) {
        case COLLIDE_DOWN:
            playerObj->setY(playerObj->getY() + colRect.h);
            world->setCameraY(world->getCameraY() + colRect.h);
            playerObj->onPlatform = true;
            break;
        case COLLIDE_UP:
            playerObj->setY(playerObj->getY() - colRect.h);
            world->setCameraY(world->getCameraY() - colRect.h);
            playerObj->onPlatform = true;
            break;
        case COLLIDE_LEFT:
            playerObj->setX(playerObj->getX() + colRect.w);
            world->setCameraX(world->getCameraX() + colRect.w);
            break;
        case COLLIDE_RIGHT:
            playerObj->setX(playerObj->getX() - colRect.w);
            world->setCameraX(world->getCameraX() - colRect.w);
            break;
        }
    }

    world->updateVolume(playerObj->entityNum, playerObj->getX(),
                        playerObj->getY(), playerObj->getW(),
                        playerObj->getH());
    // if we got hit by a spike
    if (world->collideWithSpike(playerObj)) {
        world->setPlayerDeath(true);
    }

    // if we collide with an enemy
    if (world->collideWithEnemies(playerObj)) {
        world->setPlayerDeath(true);
    }

    // if we collide with a teleport
    std::pair<bool, SDL_Rect> temp = world->collideWithTeleport(playerObj);
    if (temp.first) {
        world->setPlayerTeleport(true);
    }

    // if we collide with a checkpoint
    if (world->collideWithCheckpoint(playerObj)) {

        if (world->getCurrCheckX() != playerObj->getCheckX() ||
            world->getCurrCheckY() != playerObj->getCheckY()) {
            playerObj->sound->playSound("cp");
        }
        playerObj->setCheckX(world->getCurrCheckX());
        playerObj->setCheckY(world->getCurrCheckY());
    }

    // if we collide with a trampoline
    if (world->collideWithTrampoline(playerObj)) {
        if (!playerObj->onTrampoline) {
            if (playerObj->graphics->isUpsideDown()) {
                playerObj->sound->playSound("jump2");
                playerObj->graphics->setUpsideDown(false);
                playerObj->setYVel(-.5);
                playerObj->setY(playerObj->getY() - playerObj->getYVel() * dt);
                world->setCameraY(
                    (world->getCameraY() - playerObj->getYVel() * dt));

            } else {
                playerObj->sound->playSound("jump");
                playerObj->graphics->setUpsideDown(true);
                playerObj->setYVel(.5);
                playerObj->setY(playerObj->getY() - playerObj->getYVel() * dt);
                world->setCameraY(
                    (world->getCameraY() - playerObj->getYVel() * dt));
            }
        }
        playerObj->onTrampoline = true;
    } else {
        playerObj->onTrampoline = false;
    }
}

PlayerPhysicsComponent::~PlayerPhysicsComponent() {}
