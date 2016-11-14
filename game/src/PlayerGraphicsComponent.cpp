#include "../include/PlayerGraphicsComponent.h"
PlayerGraphicsComponent::PlayerGraphicsComponent(
    SDL_Renderer *ren, ResourceManager *r, std::vector<std::string> spritenames)
    : GraphicsComponent(ren, r, spritenames) {}

PlayerGraphicsComponent::~PlayerGraphicsComponent() {}

void PlayerGraphicsComponent::update(World *world, int dt) {

    updateCurrentSprite(world, dt);

    SDL_Rect temp = {world->transformXtoCamera(myObj->getX()),
                     world->transformYtoCamera(myObj->getY() + myObj->getH()),
                     currW, currH};

    if (SDL_RenderCopy(myRenderer, resources->getTexture(currentSprite), NULL,
                       &temp) < 0) {
        std::cout << "Something broke: " << SDL_GetError() << " "
                  << currentSprite << "\n";
    }
    updateParent();
}

void PlayerGraphicsComponent::updateCurrentSprite(World *world, int dt) {
    PlayerObject *myPlayer = (PlayerObject *)myObj;

    if (world->playerIsDead()) {
        if (currState < 16) {
            time = 0;
            if (myPlayer->getXVel() < 0) {
                if (upsideDown) {
                    currState = U_DEAD_LEFT;
                    currentSprite = spriteNames[currState];
                    SDL_SetTextureBlendMode(
                        resources->getTexture(currentSprite),
                        SDL_BLENDMODE_BLEND);

                } else {
                    currState = DEAD_LEFT;
                    currentSprite = spriteNames[currState];
                    SDL_SetTextureBlendMode(
                        resources->getTexture(currentSprite),
                        SDL_BLENDMODE_BLEND);
                }

            } else {
                if (upsideDown) {
                    currState = U_DEAD_RIGHT;
                    currentSprite = spriteNames[currState];
                    SDL_SetTextureBlendMode(
                        resources->getTexture(currentSprite),
                        SDL_BLENDMODE_BLEND);
                } else {
                    currState = DEAD_RIGHT;
                    currentSprite = spriteNames[currState];
                    SDL_SetTextureBlendMode(
                        resources->getTexture(currentSprite),
                        SDL_BLENDMODE_BLEND);
                }
            }
        }
        time += dt;
        if (time < 255) {
            SDL_SetTextureAlphaMod(resources->getTexture(currentSprite),
                                   255 - time);
        } else if (time < 510) {
            SDL_SetTextureAlphaMod(resources->getTexture(currentSprite),
                                   time - 255);
        } else if (time < 755) {
            SDL_SetTextureAlphaMod(resources->getTexture(currentSprite),
                                   755 - time);
        } else {
            SDL_SetTextureAlphaMod(
                resources->getTexture(spriteNames[U_DEAD_RIGHT]), 255);
            SDL_SetTextureAlphaMod(
                resources->getTexture(spriteNames[U_DEAD_LEFT]), 255);
            SDL_SetTextureAlphaMod(
                resources->getTexture(spriteNames[DEAD_RIGHT]), 255);
            SDL_SetTextureAlphaMod(
                resources->getTexture(spriteNames[DEAD_LEFT]), 255);
            myPlayer->respawn(world);
        }
        return;
    }

    if (myPlayer->getYVel() < 0.0 && !myPlayer->onPlatform) {
        if (myPlayer->getXVel() > 0.0) {
            currState = RIGHT_GRIN_DOWN;
        } else if (myPlayer->getXVel() < 0.0) {
            currState = LEFT_GRIN_DOWN;
        } else {
            if (currState == LEFT_GRIN_DOWN || currState == RIGHT_GRIN_DOWN) {
            } else if (currState < 8)
                currState = LEFT_GRIN_DOWN;
            else
                currState = RIGHT_GRIN_DOWN;
        }

    } else if (myPlayer->getYVel() > 0 && !myPlayer->onPlatform) {
        if (myPlayer->getXVel() > 0) {
            currState = U_RIGHT_GRIN_DOWN;
        } else if (myPlayer->getXVel() < 0) {
            currState = U_LEFT_GRIN_DOWN;
        } else {
            if (currState == U_LEFT_GRIN_DOWN ||
                currState == U_RIGHT_GRIN_DOWN) {
            } else if (currState > 3)
                currState = U_LEFT_GRIN_DOWN;
            else
                currState = U_RIGHT_GRIN_DOWN;
        }

    } else if (myPlayer->getXVel() > 0.0) {
        if (time == 0)
            time += 200;
        time += dt;
        if (time > 200) {
            time -= 200;
            if (upsideDown) {
                if (currState == U_RIGHT_GRIN_UP) {
                    currState = U_RIGHT_GRIN_DOWN;
                } else
                    currState = U_RIGHT_GRIN_UP;
            } else {

                if (currState == RIGHT_GRIN_UP) {
                    currState = RIGHT_GRIN_DOWN;
                } else
                    currState = RIGHT_GRIN_UP;
            }
        }
        if (upsideDown && currState < U_LEFT_GRIN_UP)
            currState += 8;
        else if (!upsideDown && currState > LEFT_SMILE_DOWN)
            currState -= 8;

    } else if (myPlayer->getXVel() < 0.0) {
        time += dt;
        if (time > 200) {
            time -= 200;
            if (upsideDown) {
                if (currState == U_LEFT_GRIN_UP) {
                    currState = U_LEFT_GRIN_DOWN;
                } else
                    currState = U_LEFT_GRIN_UP;
            } else {
                if (currState == LEFT_GRIN_UP) {
                    currState = LEFT_GRIN_DOWN;
                } else
                    currState = LEFT_GRIN_UP;
            }
        }
        if (upsideDown && currState > U_LEFT_SMILE_DOWN) {
            if (currState > LEFT_SMILE_DOWN)
                currState -= 4;
            currState -= 4;
        }

        else if (!upsideDown && currState < LEFT_GRIN_UP) {
            if (currState < U_LEFT_GRIN_UP)
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
