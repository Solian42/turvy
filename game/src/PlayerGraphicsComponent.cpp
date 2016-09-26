#include "../include/PlayerGraphicsComponent.h"

int centerRect(int large, int small) { return large / 2 - small / 2; }

PlayerGraphicsComponent::PlayerGraphicsComponent(std::string textureName,
                                                 SDL_Renderer *renderer) {
    SDL_Surface *image = IMG_Load(textureName.c_str());
    if (!image) {
        std::cout << "IMG_Load: " << IMG_GetError() << "\n";
    }
    this->playerSprite = SDL_CreateTextureFromSurface(renderer, image);
    if (this->playerSprite == NULL) {
        std::cout << "Something broke: " << SDL_GetError();
    }
    SDL_FreeSurface(image);
    SDL_QueryTexture(this->playerSprite, NULL, NULL, &textureW, &textureH);
}

PlayerGraphicsComponent::~PlayerGraphicsComponent() {}

void PlayerGraphicsComponent::update(PlayerObject *playerObj,
                                     SDL_Renderer *renderer, World *world) {

    SDL_Rect destination = {world->transformX(playerObj->x),
                            world->transformY(playerObj->y), textureW,
                            textureH};
    if (SDL_RenderCopy(renderer, this->playerSprite, NULL, &destination) < 0) {
        std::cout << "Something broke: " << SDL_GetError() << "\n";
    }
}

int PlayerGraphicsComponent::getTextureW() { return textureW; }
int PlayerGraphicsComponent::getTextureH() { return textureH; }
