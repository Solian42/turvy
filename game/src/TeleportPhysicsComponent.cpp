#include "../include/TeleportPhysicsComponent.h"

TeleportPhysicsComponent::TeleportPhysicsComponent() {}

bool TeleportPhysicsComponent::checkThisCollision(SDL_Rect intersect) {
    // if the intersect rect has x,y inside the coins rect range, this
    // collision.
    if (intersect.x >= myTeleport->getX() &&
        intersect.x <= myTeleport->getX() + myTeleport->getW() &&
        intersect.y >= myTeleport->getY() &&
        intersect.y <= myTeleport->getY() + myTeleport->getH()) {
        return true;
    }
    return false;
}

void TeleportPhysicsComponent::update(World *world, int dt) {

    // if player collides with Coin
    int suppressWarning = dt;
    suppressWarning++;
    temp = world->collideWithTeleport(myTeleport->playerObj);
    if (temp.first) {
        if (checkThisCollision(temp.second)) {
            world->setTeleX(myTeleport->getNewX());
            world->setTeleY(myTeleport->getNewY());
        }
    }
}

TeleportPhysicsComponent::~TeleportPhysicsComponent() {}
