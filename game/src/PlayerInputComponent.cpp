#include "../include/PlayerInputComponent.h"

PlayerInputComponent::PlayerInputComponent(World *w) { world = w; }

void PlayerInputComponent::update(SDL_Event *event, int dt) {
    SDL_Event e = *event;
    {
        // If a key was pressed
        if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
            // Adjust the velocity
            switch (e.key.keysym.sym) {
            case SDLK_SPACE:
                if (player->getY() - player->getH() <= 1) {
                    player->setYVel(MAX_ACCEL);
                    player->sound->playSound("jump");
                }
                if (player->getY() >= world->worldYLen) {
                    player->setYVel(-MAX_ACCEL);
                    player->sound->playSound("jump2");
                }
                break;
            case SDLK_LEFT:
                player->setXVel(player->getXVel() - MAX_ACCEL);
                // player->xVelocity -= MAX_ACCEL;
                break;
            case SDLK_RIGHT:
                player->setXVel(player->getXVel() + MAX_ACCEL);
                // player->xVelocity += MAX_ACCEL;
                break;
            }
        }
        // If a key was released
        else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
            // Adjust the velocity
            switch (e.key.keysym.sym) {

            case SDLK_LEFT:
                player->setXVel(player->getXVel() + MAX_ACCEL);
                // player->xVelocity += MAX_ACCEL;
                break;
            case SDLK_RIGHT:
                player->setXVel(player->getXVel() - MAX_ACCEL);
                // player->xVelocity -= MAX_ACCEL;
                break;
            }
        }
    }
    int supressWarning = dt;
    supressWarning++;
}

void PlayerInputComponent::setPlayer(PlayerObject *p) { player = p; }

PlayerInputComponent::~PlayerInputComponent() {}
