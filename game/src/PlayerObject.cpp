#include "../include/PlayerObject.h"

PlayerObject::PlayerObject(int x, int y, int velocity, PlayerInputComponent *i, 
			 PlayerGraphicsComponent *g, PlayerSoundComponent *s,
			 PlayerPhysicsComponent *p) {
	this->x = x;
	this->y = y;
	this->velocity = velocity;
	this->input = i;
	this->graphics = g;
	this->sound = s;
	this->physics = p;
}

void PlayerObject::update(World *world, SDL_Renderer *renderer) {
	this->input->update(this);
	this->graphics->update(this, renderer);
	//this->sound->update(this);
	//this->physics->update(this, world);
}

PlayerObject::~PlayerObject() {}