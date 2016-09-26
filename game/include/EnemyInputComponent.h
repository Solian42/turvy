#ifndef ENEMY_INPUT_COMPONENT_LIZARD
#define ENEMY_INPUT_COMPONENT_LIZARD

#include "EnemyObject.h"
#include "InputComponent.h"
#include <cstdlib>
#include <iostream>
#include <string>
class EnemyObject;

class EnemyInputComponent : public InputComponent {
  public:
    void update(EnemyObject *enemyObj);
    ~EnemyInputComponent();

  private:
    const int MAX_ACCEL = 10;
};

#endif
