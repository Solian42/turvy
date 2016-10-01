#ifndef PLAYER_INPUT_COMPONENT_LIZARD
#define PLAYER_INPUT_COMPONENT_LIZARD

#include "InputComponent.h"
#include "PlayerObject.h"
#include <iostream>
#include <string>
class PlayerObject;

class PlayerInputComponent : public InputComponent {
public:
    void update(PlayerObject *playerObj, SDL_Event *event, int dt);
    ~PlayerInputComponent();

private:
    const int MAX_ACCEL = 1;
};

#endif
