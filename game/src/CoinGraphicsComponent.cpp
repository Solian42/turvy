#include "../include/CoinGraphicsComponent.h"

CoinGraphicsComponent::CoinGraphicsComponent(
    SDL_Renderer *ren, ResourceManager *r, std::vector<std::string> spritenames)
    : GraphicsComponent(ren, r, spritenames) {}

CoinGraphicsComponent::~CoinGraphicsComponent() {}

void CoinGraphicsComponent::update(World *world) {

    updateCurrentSprite();
    SDL_Rect temp;
    if (myCoin->isEaten) {
        temp = {0, 0, 0, 0};
    } else {
        temp = {world->transformXtoCamera(myObj->getX()),
                world->transformYtoCamera(myObj->getY() + myObj->getH()), currW,
                currH};
        if (SDL_RenderCopy(myRenderer, resources->getTexture(currentSprite),
                           NULL, &temp) < 0) {
            std::cout << "Something broke: " << SDL_GetError() << " "
                      << currentSprite << "\n";
        }
    }
}

void CoinGraphicsComponent::updateCurrentSprite() {
    currentSprite = spriteNames[currState];
}

void CoinGraphicsComponent::setCurrState(int state) {
    currState = state;
    currentSprite = spriteNames[currState];
}
