#ifndef GAME_OBJECT_LIZARD
#define GAME_OBJECT_LIZARD

#include "World.h"
#include <SDL.h>
class GameObject {
	
	public:
	int x,y,velocity;
	GameObject(int x, int y, int velocity) {this->x = x; this->y = y; this->velocity = velocity;}
	virtual void update(World *world, SDL_Renderer *renderer);
	
	private:
	
};

#endif
