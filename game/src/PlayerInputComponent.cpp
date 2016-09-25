#include "../include/PlayerInputComponent.h"
void PlayerInputComponent::update(PlayerObject* playerObj) {
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0) {
		switch(event.type) {
			
			case SDL_KEYDOWN:
				if(event.key.keysym.sym == SDLK_UP) {
					playerObj->xVelocity = MAX_ACCEL;
				} 
				if(event.key.keysym.sym == SDLK_DOWN) {
					playerObj->xVelocity = -MAX_ACCEL;
				} 
				if(event.key.keysym.sym == SDLK_RIGHT) {
					playerObj->yVelocity = MAX_ACCEL;
				} 
				if(event.key.keysym.sym == SDLK_LEFT) {
					playerObj->yVelocity = -MAX_ACCEL;
				} 
				break;
				
				
			case SDL_KEYUP:
				if(event.key.keysym.sym == SDLK_UP) {
					playerObj->xVelocity = 0;
				} 
				if(event.key.keysym.sym == SDLK_DOWN) {
					playerObj->xVelocity = 0;
				} 
				if(event.key.keysym.sym == SDLK_RIGHT) {
					playerObj->yVelocity = 0;
				} 
				if(event.key.keysym.sym == SDLK_LEFT) {
					playerObj->yVelocity = 0;
				} 
				break;
			default:
				std::cerr << "Error: Unrecognized input\n";
				break;
		}
	}
}
			
			
	