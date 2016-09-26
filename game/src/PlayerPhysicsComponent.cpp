#include "../include/PlayerPhysicsComponent.h"

PlayerPhysicsComponent::PlayerPhysicsComponent() {}

void PlayerPhysicsComponent::update(PlayerObject *playerObj, World *world) {
    playerObj->x += playerObj->xVelocity;
    playerObj->y += playerObj->yVelocity;
    // If the player went too far to the left or right
    if ((playerObj->x < 0) ||
        (playerObj->x + playerObj->playerSpriteW > world->x)) {
        // Move back
        playerObj->x -= playerObj->xVelocity;
    }

    // If the player went too far up or down
    if (playerObj->y - playerObj->playerSpriteH < 0) {
        playerObj->y -= playerObj->yVelocity;
    } else if (playerObj->y > world->y) {
        // Move back
        playerObj->y -= playerObj->yVelocity;
    }

    world->updateVolume(playerObj->entityNum, playerObj->x, playerObj->y,
                        playerObj->playerSpriteW, playerObj->playerSpriteH);
}

PlayerPhysicsComponent::~PlayerPhysicsComponent() {}
