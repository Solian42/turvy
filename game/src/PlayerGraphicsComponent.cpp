#include "../include/PlayerGraphicsComponent.h"

PlayerGraphicsComponent::PlayerGraphicsComponent(std::string textureName, SDL_Renderer *
												 renderer) {
	SDL_Surface *image =
        IMG_Load(textureName.c_str());
    if (!image) {
        std::cout << "IMG_Load: " << IMG_GetError() << "\n";
    }
    this->playerSprite = SDL_CreateTextureFromSurface(renderer, image);	
}

PlayerGraphicsComponent::~PlayerGraphicsComponent() {}

void PlayerGraphicsComponent::update(GameObject* obj, SDL_Renderer* renderer) {}