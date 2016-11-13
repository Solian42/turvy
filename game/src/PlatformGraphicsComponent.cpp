#include "../include/PlatformGraphicsComponent.h"
PlatformGraphicsComponent::PlatformGraphicsComponent(
    SDL_Renderer *ren, ResourceManager *r, std::vector<std::string> spritenames)
    : GraphicsComponent(ren, r, spritenames) {}

PlatformGraphicsComponent::~PlatformGraphicsComponent() {}

void PlatformGraphicsComponent::update(World *world) {

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
}

void PlatformGraphicsComponent::updateCurrentSprite() {
    currW = myObj->getW();
    currH = myObj->getH();
    currentSprite = spriteNames[currState];
}

void PlatformGraphicsComponent::setCurrState(int state) {
    currState = state;
    currentSprite = spriteNames[currState];
}
