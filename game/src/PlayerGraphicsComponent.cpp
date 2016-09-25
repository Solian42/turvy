#include "../include/PlayerGraphicsComponent.h"

PlayerGraphicsComponent::PlayerGraphicsComponent(std::string textureName, SDL_Renderer *
												 renderer) {
	SDL_Surface *image =
        IMG_Load(textureName.c_str());
    if (!image) {
        std::cout << "IMG_Load: " << IMG_GetError() << "\n";
    }
    this->playerSprite = SDL_CreateTextureFromSurface(renderer, image);	
    if (this->playerSprite == NULL) {
        std::cout << "Something broke: " << SDL_GetError();
    }
    SDL_FreeSurface(image);
    
    
    
}

PlayerGraphicsComponent::~PlayerGraphicsComponent() {}

void PlayerGraphicsComponent::update(PlayerObject* playerObj, SDL_Renderer* renderer) {
	
	if(playerObj->playerRect->w == 0) {
		int textureW, textureH;
    	textureSize(this->playerSprite, &textureW, &textureH);
    	playerObj->playerRect->w = textureW;
    	playerObj->playerRect->w = textureH;
    }
    
	if (SDL_RenderCopy(renderer, this->playerSprite, NULL, playerObj->playerRect) < 0) {
            std::cout << "Something broke: " << SDL_GetError();
        }
}