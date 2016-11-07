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
    // SDL_Rect temp = {centerRect(myObj->getX(), currW),
    // centerRect(myObj->getX(), currH), currW, currH};
    if (SDL_RenderCopy(myRenderer, resources->getTexture(currentSprite), NULL,
                       &temp) < 0) {
        std::cout << "Something broke: " << SDL_GetError() << " "
                  << currentSprite << "\n";
    }
    /* Code to test Collisions. Turns things into rectangles.
    SDL_SetRenderDrawColor(myRenderer, 255, 0, 0, 255);
    SDL_RenderFillRect(myRenderer, &temp);
    SDL_SetRenderDrawColor(myRenderer, 0, 0, 0, 255);*/
    // updateParent();
}

void TrampolineGraphicsComponent::updateCurrentSprite() {

    currentSprite = spriteNames[currState];
}

void TrampolineGraphicsComponent::setCurrState(int state) {
    currState = state;
    currentSprite = spriteNames[currState];
}
