#include "../include/PlayerSoundComponent.h"

PlayerSoundComponent::PlayerSoundComponent(std::vector<std::string> chunks) {
    int i = 0;
    this->chunks = std::vector<Mix_Chunk *>(3);
    for (std::string s : chunks) {
        this->chunks[i] = Mix_LoadWAV(s.c_str());
        if (this->chunks[i] == NULL) {
            std::cout << "Failed to load low sound effect! SDL_mixer Error: "
                      << Mix_GetError() << "\n";
        }
    }
}

void PlayerSoundComponent::update(World *world) {
    int i;
    if (world->collision == true) {
        i = 0;
        Mix_PlayChannel(-1, this->chunks[i], 0);
    }
}

PlayerSoundComponent::~PlayerSoundComponent() {}
