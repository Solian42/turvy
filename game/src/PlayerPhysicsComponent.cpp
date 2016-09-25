#include "../include/PlayerPhysicsComponent.h"

PlayerPhysicsComponent::PlayerPhysicsComponent() {}

void PlayerPhysicsComponent::update(PlayerObject* playerObj, World* world) {
	playerObj->x += playerObj->xVelocity;
	playerObj->y += playerObj->yVelocity;
	
	int x = world->transformX(playerObj->x);
	int y = world->transformY(playerObj->y);

	playerObj->playerRect->x = x;
	playerObj->playerRect->y = y;
	
	//collisions?
}

PlayerPhysicsComponent::~PlayerPhysicsComponent() {}
	