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
    PlayerSoundComponent(std::vector<std::string> chunks, ResourceManager *r);
    void update(World *world);
    void playSound(std::string soundName);
    void setPlayerObj(PlayerObject *obj);
    void respawn() { hasDied = false; }
    ~PlayerSoundComponent();

private:
    bool hasDied = false;
    PlayerObject *player;
    ResourceManager *resources;
    std::vector<std::string> chunks;
};

#endif
