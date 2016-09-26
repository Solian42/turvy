#ifndef ENEMY_PHYSICS_COMPONENT_LIZARD
#define ENEMY_PHYSICS_COMPONENT_LIZARD

#include "EnemyObject.h"
#include "PhysicsComponent.h"
#include <iostream>
#include <string>
class EnemyObject;

class EnemyPhysicsComponent : public PhysicsComponent {
  public:
    EnemyPhysicsComponent();
    void update(EnemyObject *enemyObj, World *world);
    ~EnemyPhysicsComponent();

  private:
};

#endif