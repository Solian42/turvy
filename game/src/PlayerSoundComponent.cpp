#include "../include/PlayerSoundComponent.h"

PlayerSoundComponent::PlayerSoundComponent(std::vector<std::string> chunks,
                                           ResourceManager *r) {
    this->chunks = chunks;
    resources = r;
}

void PlayerSoundComponent::update(World *world) {
    int i;
    if (world->collision == true) {
        i = 0;
        // Mix_PlayChannel(-1, resources->getChunk(chunks[i]), 0);
    }
}

PlayerSoundComponent::~PlayerSoundComponent() {}
