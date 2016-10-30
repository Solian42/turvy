#ifndef COIN_PHYSICS_COMPONENT_LIZARD
#define COIN_PHYSICS_COMPONENT_LIZARD

#include "PhysicsComponent.h"
#include "CoinObject.h"
#include <iostream>
#include <string>
class CoinObject;

class CoinPhysicsComponent : public PhysicsComponent {
public:
    CoinPhysicsComponent();
    void update(CoinObject *coinObj, World *world, int dt);
    ~CoinPhysicsComponent();
};

#endif
