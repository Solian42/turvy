#ifndef PHYSICS_COMPONENT_LIZARD
#define PHYSICS_COMPONENT_LIZARD

#include "GameObject.h"
#include "World.h"
#include <SDL.h>

class World;
class PhysicsComponent {
public:
    virtual ~PhysicsComponent() {}
    void update(GameObject *obj, World *world, int dt);
};

#endif
