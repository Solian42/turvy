#ifndef ENEMY_PHYSICS_COMPONENT_LIZARD
#define ENEMY_PHYSICS_COMPONENT_LIZARD

#include "PhysicsComponent.h"
#include "EnemyObject.h"
#include <string>
#include <iostream>
class EnemyObject;

class EnemyPhysicsComponent : public PhysicsComponent
{
public:
	EnemyPhysicsComponent();
  	void update(EnemyObject* enemyObj, World* world);
  	~EnemyPhysicsComponent();
  	
  	
  	private:
};


#endif