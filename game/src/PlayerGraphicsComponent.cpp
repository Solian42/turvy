#include "../include/PlayerGraphicsComponent.h"
PlayerGraphicsComponent::PlayerGraphicsComponent(
    SDL_Renderer *ren, ResourceManager *r, std::vector<std::string> spritenames)
    : GraphicsComponent(ren, r, spritenames) {}

PlayerGraphicsComponent::~PlayerGraphicsComponent() {}

void PlayerGraphicsComponent::update(World *world, int dt) {

    updateCurrentSprite(dt);

    SDL_Rect temp = {world->transformXtoCamera(myObj->getX()),
                     world->transformYtoCamera(myObj->getY()+ myObj->getH()), currW, currH};
    // SDL_Rect temp = {centerRect(myObj->getX(), currW),
    // centerRect(myObj->getX(), currH), currW, currH};

    if (SDL_RenderCopy(myRenderer, resources->getTexture(currentSprite), NULL,
                       &temp) < 0) {
        std::cout << "Something broke: " << SDL_GetError() << " "
                  << currentSprite << "\n";
    }
	/*//Code to test Collisions. Turns things into rectangles.
    SDL_SetRenderDrawColor(myRenderer, 255, 0, 0, 255);
    SDL_RenderFillRect(myRenderer, &temp);
    SDL_SetRenderDrawColor(myRenderer, 0, 0, 0, 255);*/
    updateParent();
}

void PlayerGraphicsComponent::updateCurrentSprite(int dt) {
    // TODO:Logic for current sprite

    if (myObj->getYVel() < 0.0) {
        if (myObj->getXVel() > 0.0) {
            currState = RIGHT_GRIN_DOWN;
        } else if (myObj->getXVel() < 0.0) {
            currState = LEFT_GRIN_DOWN;
        } else {
			if ( currState ==  LEFT_GRIN_DOWN || currState == RIGHT_GRIN_DOWN) {
			} else if (currState < 8) currState = LEFT_GRIN_DOWN;
			else currState = RIGHT_GRIN_DOWN;
        }

    } else if (myObj->getYVel() > 0) {
        if (myObj->getXVel() > 0) {
            currState = U_RIGHT_GRIN_DOWN;
        } else if (myObj->getXVel() < 0) {
            currState = U_LEFT_GRIN_DOWN;
        } else {
			if ( currState ==  U_LEFT_GRIN_DOWN || currState == U_RIGHT_GRIN_DOWN) {
			} else if (currState > 3) currState = U_LEFT_GRIN_DOWN;
			else currState = U_RIGHT_GRIN_DOWN;
        }

    } else if (myObj->getXVel() > 0.0) {
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

    } else if (myObj->getXVel() < 0.0) {
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
