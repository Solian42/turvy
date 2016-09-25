#ifndef PHYSICS_COMPONENT_LIZARD
#define PHYSICS_COMPONENT_LIZARD

#include "GameObject.h"
#include "World.h"
class PhysicsComponent
{
public:
  virtual ~PhysicsComponent() {}
  virtual void update(GameObject& obj, World& world) = 0;
};

#endif
