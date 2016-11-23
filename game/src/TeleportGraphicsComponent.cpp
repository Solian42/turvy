#include "../include/TeleportGraphicsComponent.h"

TeleportGraphicsComponent::TeleportGraphicsComponent(
    SDL_Renderer *ren, ResourceManager *r, std::vector<std::string> spritenames)
    : GraphicsComponent(ren, r, spritenames) {

        SDL_QueryTexture(resources->getTexture("destination1"), NULL, NULL, &currW,
                     &currH);  
    }

TeleportGraphicsComponent::~TeleportGraphicsComponent() {}

void TeleportGraphicsComponent::update(World *world, int dt) {

    updateCurrentSprite(dt);

    SDL_Rect temp = {world->transformXtoCamera(myTeleport->getX()),
                     world->transformYtoCamera(myTeleport->getY() + myTeleport->getH()),
                     currW, currH};

    if (SDL_RenderCopy(myRenderer, resources->getTexture(currentSprite), NULL,
                       &temp) < 0) {
        std::cout << "Something broke: " << SDL_GetError() << " "
                  << currentSprite << "\n";
    }

    SDL_Rect tempDest = {world->transformXtoCamera(myTeleport->getNewX()),
                         world->transformYtoCamera(myTeleport->getNewY() + myTeleport->getH()),
                         currW, currH};
    if (SDL_RenderCopy(myRenderer, resources->getTexture("destination1"), NULL,
                       &tempDest) < 0) {
        std::cout << "Something broke: " << SDL_GetError() << " "
                  << "destination1" << "\n";
    } 
}

void TeleportGraphicsComponent::updateCurrentSprite(int dt) {
    time += dt;
    if (time > 200) {
        time -= 200;
        switch (currState) {
        case 0:
            currState = 1;
            break;
        case 1:
            currState = 2;
            break;

        case 2:
            currState = 0;
            break;

        default:
            break;
        }
    }
    currentSprite = spriteNames[currState];
}

void TeleportGraphicsComponent::setCurrState(int state) {
    currState = state;
    currentSprite = spriteNames[currState];
}
