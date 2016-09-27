#ifndef PLAYER_SOUND_COMPONENT_LIZARD
#define PLAYER_SOUND_COMPONENT_LIZARD

#include "PlayerObject.h"
#include "SoundComponent.h"
#include <SDL_mixer.h>
#include <iostream>
#include <string>
#include <vector>
class PlayerObject;

class PlayerSoundComponent : public SoundComponent {
public:
    PlayerSoundComponent(std::vector<std::string> chunks);
    void update(World *world);
    ~PlayerSoundComponent();

private:
    std::vector<Mix_Chunk *> chunks;
};

#endif
