#include "../include/DialogueGraphicsComponent.h"

DialogueGraphicsComponent::DialogueGraphicsComponent(
    SDL_Renderer *ren, ResourceManager *r, std::vector<std::string> spritenames)
    : GraphicsComponent(ren, r, spritenames) {}

DialogueGraphicsComponent::~DialogueGraphicsComponent() {}

void DialogueGraphicsComponent::update(World *world) {
    if (myTexture == nullptr) {
        updateCurrentSprite();
    }
    SDL_Rect temp;
    if (myDialogue->skip) {
        temp = {0, 0, 0, 0};
    } else {
        temp = {world->transformXtoCamera(myObj->getX()),
                world->transformYtoCamera(myObj->getY() + myObj->getH()), currW,
                currH};
        if (SDL_RenderCopy(myRenderer, myTexture, NULL, &temp) < 0) {
            std::cout << "Something broke: " << SDL_GetError() << " "
                      << currentSprite << "\n";
        }
    }
}

void DialogueGraphicsComponent::updateCurrentSprite() {
    if (myTexture != nullptr) {
        SDL_DestroyTexture(myTexture);
    }
    myTexture = SDL_CreateTexture(myRenderer, SDL_PIXELFORMAT_RGBA8888,
                                  SDL_TEXTUREACCESS_TARGET, myObj->getW(),
                                  myObj->getH());
    SDL_SetTextureBlendMode(myTexture, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(myRenderer, 0, 0, 0, 0);
    SDL_SetRenderTarget(myRenderer, myTexture);
    SDL_RenderClear(myRenderer);
    SDL_Rect temp = {0, 0, currW, currH};
    if (SDL_RenderCopy(myRenderer, resources->getTexture(currentSprite), NULL,
                       &temp) < 0) {
        std::cout << "Something broke: " << SDL_GetError() << " "
                  << currentSprite << "\n";
    }

    currentSprite = spriteNames[currState];
    SDL_SetRenderTarget(myRenderer, NULL);
}

void DialogueGraphicsComponent::setCurrState(int state) {
    currState = state;
    currentSprite = spriteNames[currState];
}
