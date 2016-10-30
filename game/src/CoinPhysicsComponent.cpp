#include "../include/CoinPhysicsComponent.h"

CoinPhysicsComponent::CoinPhysicsComponent() {}

void CoinPhysicsComponent::update(CoinObject *coinObj, World *world, int dt) {

    // if player collides with Coin
    if (world->collideWithCoin(coinObj->playerObj)) {
        if (coinObj->notEaten) {
            world->coinCollision = true;
            coinObj->notEaten = false;
        }
    }
}

CoinPhysicsComponent::~CoinPhysicsComponent() {}
