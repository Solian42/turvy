#include "../include/PlayerInputComponent.h"
void PlayerInputComponent::update(PlayerObject *playerObj, SDL_Event *event, int dt) {
    SDL_Event e = *event;
    {
        // If a key was pressed
        if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
            // Adjust the velocity
            switch (e.key.keysym.sym) {
            case SDLK_UP:
                playerObj->setYVel(playerObj->getYVel() + MAX_ACCEL);
                //playerObj->yVelocity += MAX_ACCEL;
                break;
            case SDLK_DOWN:
                playerObj->setYVel(playerObj->getYVel() - MAX_ACCEL);
                //playerObj->yVelocity -= MAX_ACCEL;
                break;
            case SDLK_LEFT:
                playerObj->setXVel(playerObj->getXVel() - MAX_ACCEL);
                //playerObj->xVelocity -= MAX_ACCEL;
                break;
            case SDLK_RIGHT:
                playerObj->setXVel(playerObj->getXVel() + MAX_ACCEL);
                //playerObj->xVelocity += MAX_ACCEL;
                break;
            }
        }
        // If a key was released
        else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
            // Adjust the velocity
            switch (e.key.keysym.sym) {
            case SDLK_UP:
                playerObj->setYVel(playerObj->getYVel() - MAX_ACCEL);
                //playerObj->yVelocity -= MAX_ACCEL;
                break;
            case SDLK_DOWN:
                playerObj->setYVel(playerObj->getYVel() + MAX_ACCEL);
                //playerObj->yVelocity += MAX_ACCEL;
                break;
            case SDLK_LEFT:
                playerObj->setXVel(playerObj->getXVel() + MAX_ACCEL);
                //playerObj->xVelocity += MAX_ACCEL;
                break;
            case SDLK_RIGHT:
                playerObj->setXVel(playerObj->getXVel() - MAX_ACCEL);
                //playerObj->xVelocity -= MAX_ACCEL;
                break;
            }
        }
    }
}

PlayerInputComponent::~PlayerInputComponent() {}
