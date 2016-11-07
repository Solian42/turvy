#include "../include/CheckpointGraphicsComponent.h"

CheckpointGraphicsComponent::CheckpointGraphicsComponent(
    SDL_Renderer *ren, ResourceManager *r, std::vector<std::string> spritenames)
    : GraphicsComponent(ren, r, spritenames) {}

CheckpointGraphicsComponent::~CheckpointGraphicsComponent() {}

void CheckpointGraphicsComponent::update(World *world) {

    updateCurrentSprite(world);

    SDL_Rect temp = {world->transformXtoCamera(myObj->getX()),
                     world->transformYtoCamera(myObj->getY() + myObj->getH()),
                     currW, currH};

    if (SDL_RenderCopy(myRenderer, resources->getTexture(currentSprite), NULL,
                       &temp) < 0) {
        std::cout << "Something broke: " << SDL_GetError() << " "
                  << currentSprite << "\n";
    }
}

void CheckpointGraphicsComponent::updateCurrentSprite(World *world) {
    if (world->getCurrCheckX() == myObj->getX() &&
        world->getCurrCheckY() == myObj->getY()) {
        currState = 1;
    } else {
        currState = 0;
    }
    currentSprite = spriteNames[currState];
    scaleCurrentSprite(2);
}

void CheckpointGraphicsComponent::setCurrState(int state) {
    currState = state;
    currentSprite = spriteNames[currState];
}
