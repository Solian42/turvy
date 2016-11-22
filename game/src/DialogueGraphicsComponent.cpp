#include "../include/DialogueGraphicsComponent.h"

DialogueGraphicsComponent::DialogueGraphicsComponent(
    SDL_Renderer *ren, ResourceManager *r, std::vector<std::string> spritenames)
    : GraphicsComponent(ren, r, spritenames) {}

DialogueGraphicsComponent::~DialogueGraphicsComponent() {}

void DialogueGraphicsComponent::update(World *world) {

    updateCurrentSprite();
    SDL_Rect temp;
    if (myDialogue->skip) {
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

void DialogueGraphicsComponent::updateCurrentSprite() {

    currentSprite = spriteNames[currState];
}

void DialogueGraphicsComponent::setCurrState(int state) {
    currState = state;
    currentSprite = spriteNames[currState];
}
