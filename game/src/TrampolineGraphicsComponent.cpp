#include "../include/TrampolineGraphicsComponent.h"
TrampolineGraphicsComponent::TrampolineGraphicsComponent(
    SDL_Renderer *ren, ResourceManager *r, std::vector<std::string> spritenames)
    : GraphicsComponent(ren, r, spritenames) {}

TrampolineGraphicsComponent::~TrampolineGraphicsComponent() {}

void TrampolineGraphicsComponent::update(World *world) {

    updateCurrentSprite();

    SDL_Rect temp = {world->transformXToWorld(myObj->getX()),
                     world->transformYToWorld(myObj->getY() + myObj->getH()),
                     currW, currH};
    if (SDL_RenderCopy(myRenderer, resources->getTexture(currentSprite), NULL,
                       &temp) < 0) {
        std::cout << "Something broke: " << SDL_GetError() << " "
                  << currentSprite << "\n";
    }
}

void TrampolineGraphicsComponent::updateCurrentSprite() {

    currentSprite = spriteNames[currState];
}

void TrampolineGraphicsComponent::setCurrState(int state) {
    currState = state;
    currentSprite = spriteNames[currState];
}
