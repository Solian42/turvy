#ifndef PLAYER_INPUT_COMPONENT_LIZARD
#define PLAYER_INPUT_COMPONENT_LIZARD

#include "InputComponent.h"
#include "PlayerObject.h"
#include <string>
#include <iostream>
class PlayerObject;

class PlayerInputComponent : public InputComponent
{
public:
  	void update(PlayerObject* playerObj);
  	~PlayerInputComponent();
  	
  	
  	private:
  	const int MAX_ACCEL = 1;
};


#endif