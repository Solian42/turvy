#include "../include/PlayerGraphicsComponent.h"
PlayerGraphicsComponent::PlayerGraphicsComponent(
    SDL_Renderer *ren, ResourceManager *r, std::vector<std::string> spritenames)
    : GraphicsComponent(ren, r, spritenames) {}

PlayerGraphicsComponent::~PlayerGraphicsComponent() {}

void PlayerGraphicsComponent::update(World *world, int dt) {

    updateCurrentSprite(dt);

    SDL_Rect temp = {world->transformXtoCamera(myObj->getX()),
                     world->transformYtoCamera(myObj->getY()), currW, currH};
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
    updateParent();
}

void PlayerGraphicsComponent::updateCurrentSprite(int dt) {
    // TODO:Logic for current sprite
    if (myObj->getY() > 500) {
        upsideDown = true;

    } else {
        upsideDown = false;
    }

    if (myObj->getYVel() < 0) {

        if (myObj->getXVel() > 0) {
            currState = 1;
        } else if (myObj->getXVel() < 0) {
            currState = 9;
        } else if (upsideDown) {
            currState = 9;
        }

    } else if (myObj->getYVel() > 0) {
        if (myObj->getXVel() > 0) {
            currState = 13;
        } else if (myObj->getXVel() < 0) {
            currState = 5;
        } else if (!upsideDown) {
            currState = 5;
        }

    } else if (myObj->getXVel() > 0.0) {
        if (time == 0)
            time += 200;
        time += dt;
        if (time > 200) {
            time -= 200;
            if (upsideDown) {
                if (currState == 12) {
                    currState = 13;
                } else
                    currState = 12;
            } else {

                if (currState == 0) {
                    currState = 1;
                } else
                    currState = 0;
            }
        }
        if (upsideDown && currState < 4)
            currState += 8;
        else if (!upsideDown && currState > 11)
            currState -= 8;

    } else if (myObj->getXVel() < 0.0) {
        time += dt;
        if (time > 200) {
            time -= 200;
            if (upsideDown) {
                if (currState == 4) {
                    currState = 5;
                } else
                    currState = 4;
            } else {
                if (currState == 8) {
                    currState = 9;
                } else
                    currState = 8;
            }
        }
        if (upsideDown && currState > 7) {
            if (currState > 11)
                currState -= 4;
            currState -= 4;
        }

        else if (!upsideDown && currState < 8) {
            if (currState < 4)
                currState += 4;
            currState += 4;
        }
    } else if (time > 0) {
        time = 0;
        if (currState % 2 != 0)
            currState--;
    }
    currentSprite = spriteNames[currState];
    scaleCurrentSprite(2);
}

void PlayerGraphicsComponent::setCurrState(int state) {
    currState = state;
    currentSprite = spriteNames[currState];
}
