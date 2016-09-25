#include "../include/PlayerObject.h"

PlayerObject::PlayerObject(int x, int y, int xVelocity, int yVelocity,
						   PlayerInputComponent *i, PlayerGraphicsComponent *g,
						   PlayerSoundComponent *s, PlayerPhysicsComponent *p) {
	this->x = x;
	this->y = y;
	this->xVelocity = xVelocity;
	this->yVelocity = yVelocity;
	this->input = i;
	this->graphics = g;
	this->sound = s;
	this->physics = p;
	SDL_Rect startRect = {0,0,0,0};
	this->playerRect = &startRect; 
	
}

void PlayerObject::update(World *world, SDL_Renderer *renderer) {
	this->input->update(this);
	this->physics->update(this, world);
	this->graphics->update(this, renderer);
	//this->sound->update(this);
	
	
}

PlayerObject::~PlayerObject() {}