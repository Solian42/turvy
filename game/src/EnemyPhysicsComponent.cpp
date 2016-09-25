#include "../include/EnemyPhysicsComponent.h"

EnemyPhysicsComponent::EnemyPhysicsComponent() {}

void EnemyPhysicsComponent::update(EnemyObject* enemyObj, World* world) {
	enemyObj->x += enemyObj->xVelocity;
	enemyObj->y += enemyObj->yVelocity;
	
	//int x = world->transformX(enemyObj->x);
	//int y = world->transformY(enemyObj->y);
	int x = 0;
	int y = 0;
	enemyObj->enemyRect->x = x;
	enemyObj->enemyRect->y = y;
	
	//collisions?
}

EnemyPhysicsComponent::~EnemyPhysicsComponent() {}
	