#include "../include/PlayerInputComponent.h"
void PlayerInputComponent::update(PlayerObject *playerObj, SDL_Event *event) {
    SDL_Event e = *event;
    {
        // If a key was pressed
        if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
            // Adjust the velocity
            switch (e.key.keysym.sym) {
            case SDLK_UP:
                playerObj->yVelocity += MAX_ACCEL;
                break;
            case SDLK_DOWN:
                playerObj->yVelocity -= MAX_ACCEL;
                break;
            case SDLK_LEFT:
                playerObj->xVelocity -= MAX_ACCEL;
                break;
            case SDLK_RIGHT:
                playerObj->xVelocity += MAX_ACCEL;
                break;
            }
        }
        // If a key was released
        else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
            // Adjust the velocity
            switch (e.key.keysym.sym) {
            case SDLK_UP:
                playerObj->yVelocity -= MAX_ACCEL;
                break;
            case SDLK_DOWN:
                playerObj->yVelocity += MAX_ACCEL;
                break;
            case SDLK_LEFT:
                playerObj->xVelocity += MAX_ACCEL;
                break;
            case SDLK_RIGHT:
                playerObj->xVelocity -= MAX_ACCEL;
                break;
            }
        }
    }
}

PlayerInputComponent::~PlayerInputComponent() {}
