#ifndef PLAYER_INPUT_COMPONENT_LIZARD
#define PLAYER_INPUT_COMPONENT_LIZARD

#include "InputComponent.h"
#include "PlayerObject.h"
#include <iostream>
#include <string>
class PlayerObject;

class PlayerInputComponent : public InputComponent {
public:
    void setPlayer(PlayerObject *p);
    void update(SDL_Event *event, int dt);
    ~PlayerInputComponent();

private:
    PlayerObject *player;
    const float MAX_ACCEL = .5;
};

#endif
