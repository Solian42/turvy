#include "../include/CheckpointGraphicsComponent.h"

CheckpointGraphicsComponent::CheckpointGraphicsComponent(
    SDL_Renderer *ren, ResourceManager *r, std::vector<std::string> spritenames)
    : GraphicsComponent(ren, r, spritenames) {}

CheckpointGraphicsComponent::~CheckpointGraphicsComponent() {}

void CheckpointGraphicsComponent::update(World *world) {

    updateCurrentSprite();

    SDL_Rect temp = {world->transformXtoCamera(myObj->getX()),
                     world->transformYtoCamera(myObj->getY() + myObj->getH()),
                     currW, currH};

    if (SDL_RenderCopy(myRenderer, resources->getTexture(currentSprite), NULL,
                       &temp) < 0) {
        std::cout << "Something broke: " << SDL_GetError() << " "
                  << currentSprite << "\n";
    }
}

void CheckpointGraphicsComponent::updateCurrentSprite() {
    currentSprite = spriteNames[currState];
}

void CheckpointGraphicsComponent::setCurrState(int state) {
    currState = state;
    currentSprite = spriteNames[currState];
}
