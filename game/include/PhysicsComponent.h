#ifndef PHYSICS_COMPONENT_LIZARD
#define PHYSICS_COMPONENT_LIZARD

#include "GameObject.h"
#include "World.h"
#include <SDL.h>
class PhysicsComponent {
  public:
    virtual ~PhysicsComponent() {}
    void update(GameObject *obj, World *world);
};

#endif
