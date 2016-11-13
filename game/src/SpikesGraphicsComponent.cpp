#include "../include/SpikesGraphicsComponent.h"
SpikesGraphicsComponent::SpikesGraphicsComponent(
    SDL_Renderer *ren, ResourceManager *r, std::vector<std::string> spritenames)
    : GraphicsComponent(ren, r, spritenames) {}

SpikesGraphicsComponent::~SpikesGraphicsComponent() {}

void SpikesGraphicsComponent::update(World *world) {

    updateCurrentSprite();

    SDL_Rect temp = {world->transformXToWorld(myObj->getX()),
                     world->transformYToWorld(myObj->getY() + myObj->getH()),
                     currW, currH};
    SpikesObject *mySpike = (SpikesObject *)myObj;
    int o = mySpike->getOrientation();
    switch (o) {
    case 0:
        SDL_RenderCopyEx(myRenderer, resources->getTexture(currentSprite), NULL,
                         &temp, 0.0, NULL, SDL_FLIP_NONE);
        break;
    case 1:
        SDL_RenderCopyEx(myRenderer, resources->getTexture(currentSprite), NULL,
                         &temp, 0.0, NULL, SDL_FLIP_VERTICAL);
        break;
    case 2:
        SDL_RenderCopyEx(myRenderer, resources->getTexture(currentSprite), NULL,
                         &temp, 90.0, NULL, SDL_FLIP_NONE);
        break;

    case 3:
        SDL_RenderCopyEx(myRenderer, resources->getTexture(currentSprite), NULL,
                         &temp, -90.0, NULL, SDL_FLIP_NONE);
        break;
    }
}

void SpikesGraphicsComponent::updateCurrentSprite() {
    currentSprite = spriteNames[currState];
}

void SpikesGraphicsComponent::setCurrState(int state) {
    currState = state;
    currentSprite = spriteNames[currState];
}
