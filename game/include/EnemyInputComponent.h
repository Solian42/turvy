#ifndef ENEMY_INPUT_COMPONENT_LIZARD
#define ENEMY_INPUT_COMPONENT_LIZARD

#include "InputComponent.h"
#include "EnemyObject.h"
#include <string>
#include <iostream>
class EnemyObject;

class EnemyInputComponent : public InputComponent
{
public:
  	void update(EnemyObject* enemyObj);
  	~EnemyInputComponent();
  	
  	
  	private:
  	const int MAX_ACCEL = 1;
};


#endif