#include "../include/EnemyObject.h"


EnemyObject::EnemyObject(int x, int y, int xVelocity, int yVelocity, EnemyInputComponent *i, EnemyGraphicsComponent *g,
				 EnemyPhysicsComponent *p){
	this->x = x;
	this->y = y;
	this->xVelocity = xVelocity;
	this->yVelocity = yVelocity;
	this->input = i;
	this->graphics = g;
	this->physics = p;
	SDL_Rect startRect = {0,0,0,0};
	this->enemyRect = &startRect; 
}

void EnemyObject::update(World *world, SDL_Renderer *renderer){
	this->input->update(this);
	this->graphics->update(this, renderer);
	// this->physics->update(this, world);
}

EnemyObject::~EnemyObject() {}
