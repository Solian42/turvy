#ifndef PLAYER_OBJECT_LIZARD
#define PLAYER_OBJECT_LIZARD

#include "GameObject.h"
#include "InputComponent.h"
#include "GraphicsComponent.h"
#include "SoundComponent.h"
#include "PhysicsComponent.h"
class PlayerObject: public GameObject {
	
	public:
	int x,y,velocity;
	PlayerObject(int x, int y, int velocity, InputComponent *i, GraphicsComponent *g,
				 SoundComponent *s, PhysicsComponent *p);
	void update(World * world, SDL_Renderer *renderer);
	
	private:
	InputComponent * input;
	GraphicsComponent *graphics;
	SoundComponent *sound;
	PhysicsComponent *physics;
};

#endif
