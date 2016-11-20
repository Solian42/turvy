#ifndef TELEPORT_PHYSICS_COMPONENT_LIZARD
#define TELEPORT_PHYSICS_COMPONENT_LIZARD

#include "TeleportObject.h"
#include "PhysicsComponent.h"
#include <iostream>
#include <string>
class TeleportObject;

class TeleportPhysicsComponent : public PhysicsComponent {
public:
    TeleportPhysicsComponent();

    void update(World *world, int dt);
    ~TeleportPhysicsComponent();
    TeleportObject *myTeleport = nullptr;
    bool checkThisCollision(SDL_Rect);

private:
    std::pair<bool, SDL_Rect> temp;
};

#endif
