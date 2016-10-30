#include "../include/SpikesGraphicsComponent.h"
SpikesGraphicsComponent::SpikesGraphicsComponent(
    SDL_Renderer *ren, ResourceManager *r, std::vector<std::string> spritenames)
    : GraphicsComponent(ren, r, spritenames) {}

SpikesGraphicsComponent::~SpikesGraphicsComponent() {}

void SpikesGraphicsComponent::update(World *world) {

    updateCurrentSprite((SpikesObject *)myObj);

    SDL_Rect temp = {world->transformXtoCamera(myObj->getX()),
                     world->transformYtoCamera(myObj->getY() + myObj->getH()),
                     currW, currH};
    // SDL_Rect temp = {centerRect(myObj->getX(), currW),
    // centerRect(myObj->getX(), currH), currW, currH};
    SpikesObject *mySpike = (SpikesObject *)myObj;
    if (mySpike->isUpsideDown()) {
        SDL_RenderCopyEx(myRenderer, resources->getTexture(currentSprite), NULL,
                         &temp, 0.0, NULL, SDL_FLIP_VERTICAL);
    } else {
        if (SDL_RenderCopy(myRenderer, resources->getTexture(currentSprite),
                           NULL, &temp) < 0) {
            std::cout << "Something broke: " << SDL_GetError() << " "
                      << currentSprite << "\n";
        }
    }
    /* Code to test Collisions. Turns things into rectangles.
    SDL_SetRenderDrawColor(myRenderer, 255, 0, 0, 255);
    SDL_RenderFillRect(myRenderer, &temp);
    SDL_SetRenderDrawColor(myRenderer, 0, 0, 0, 255);*/
    // updateParent();
}

void SpikesGraphicsComponent::updateCurrentSprite(SpikesObject *spikes) {

    /* Sets the sprite based on orientation. */
    /*if (spikes->isUpsideDown()) {
        currState = 1;
    } else {
        currState = 0;
    }*/

    currentSprite = spriteNames[currState];
}

void SpikesGraphicsComponent::setCurrState(int state) {
    currState = state;
    currentSprite = spriteNames[currState];
}
