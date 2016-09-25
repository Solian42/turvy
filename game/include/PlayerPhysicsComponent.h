#ifndef PLAYER_PHYSICS_COMPONENT_LIZARD
#define PLAYER_PHYSICS_COMPONENT_LIZARD

#include "PhysicsComponent.h"
#include "PlayerObject.h"
#include <string>
#include <iostream>
class PlayerObject;

class PlayerPhysicsComponent : public PhysicsComponent
{
public:
	PlayerPhysicsComponent();
  	void update(PlayerObject* playerObj, World* world);
  	~PlayerPhysicsComponent();
  	
  	
  	private:
};


#endif