#ifndef COIN_PHYSICS_COMPONENT_LIZARD
#define COIN_PHYSICS_COMPONENT_LIZARD

#include "CoinObject.h"
#include "PhysicsComponent.h"
#include <iostream>
#include <string>
class CoinObject;

class CoinPhysicsComponent : public PhysicsComponent {
public:
    CoinPhysicsComponent();

    void update(World *world, int dt);
    ~CoinPhysicsComponent();
    CoinObject *myCoin = nullptr;
    bool checkThisCollision(SDL_Rect);

private:
    std::pair<bool, SDL_Rect> temp;
};

#endif
