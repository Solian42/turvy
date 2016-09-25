#ifndef GAME_OBJECT_LIZARD
#define GAME_OBJECT_LIZARD

#include "World.h"
#include <SDL.h>
class GameObject {
	
	public:
	int x,y,velocity;
	void update(World *world, SDL_Renderer *renderer);
	
};

#endif
