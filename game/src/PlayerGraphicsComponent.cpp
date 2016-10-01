#include "../include/PlayerGraphicsComponent.h"
PlayerGraphicsComponent::PlayerGraphicsComponent(SDL_Renderer * ren, ResourceManager *r, std::vector<std::string> spritenames) : GraphicsComponent(ren, r, spritenames){
}


PlayerGraphicsComponent::~PlayerGraphicsComponent() {}

void PlayerGraphicsComponent::updateCurrentSprite() {
    //TODO:Logic for current sprite
    currentSprite = spriteNames[0];
}



