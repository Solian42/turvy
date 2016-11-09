#include "../include/CoinPhysicsComponent.h"

CoinPhysicsComponent::CoinPhysicsComponent() {}

void CoinPhysicsComponent::update(World *world, int dt) {

    // if player collides with Coin
    if (world->collideWithCoin(myCoin->playerObj)) {
        if (!myCoin->isEaten) {
            world->setCoinCollision(true);
            myCoin->isEaten = true;
            // std::printf(coinObj->isEaten ? "true" : "false");
        }
    }
}

CoinPhysicsComponent::~CoinPhysicsComponent() {}
