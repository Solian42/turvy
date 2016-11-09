#include "../include/CoinPhysicsComponent.h"

CoinPhysicsComponent::CoinPhysicsComponent() {}

void CoinPhysicsComponent::update(CoinObject *coinObj, World *world, int dt) {

    // if player collides with Coin
    if (world->collideWithCoin(coinObj->playerObj)) {
        if (!coinObj->isEaten) {
            world->setCoinCollision(true);
            coinObj->isEaten = true;
            // std::printf(coinObj->isEaten ? "true" : "false");
        }
    }
}

CoinPhysicsComponent::~CoinPhysicsComponent() {}
