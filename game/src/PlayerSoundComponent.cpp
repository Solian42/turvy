#include "../include/PlayerSoundComponent.h"

PlayerSoundComponent::PlayerSoundComponent(std::vector<std::string> chunks,
                                           ResourceManager *r) {
    this->chunks = chunks;
    resources = r;
}

void PlayerSoundComponent::update(World *world) {
    if (world->collision) {
        Mix_PlayChannel(-1, resources->getChunk("hurt"), 0);
    }
}

void PlayerSoundComponent::playSound(std::string soundName) {

    Mix_PlayChannel(-1, resources->getChunk(soundName), 0);
}
PlayerSoundComponent::~PlayerSoundComponent() {}
