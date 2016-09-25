#ifndef PLAYER_OBJECT_LIZARD
#define PLAYER_OBJECT_LIZARD

#include "GameObject.h"
#include "PlayerInputComponent.h"
#include "PlayerGraphicsComponent.h"
#include "PlayerSoundComponent.h"
#include "PlayerPhysicsComponent.h"

class PlayerGraphicsComponent;
class PlayerInputComponent;
class PlayerPhysicsComponent;
class PlayerSoundComponent;

class PlayerObject: public GameObject {
	
	public:
	int x,y,velocity;
	PlayerObject(int x, int y, int velocity, PlayerInputComponent *i, PlayerGraphicsComponent *g,
				 PlayerSoundComponent *s, PlayerPhysicsComponent *p);
	void update(World * world, SDL_Renderer *renderer);
	
	~PlayerObject();
	private:
	
	PlayerInputComponent * input;
	PlayerGraphicsComponent *graphics;
	PlayerSoundComponent *sound;
	PlayerPhysicsComponent *physics;
};

#endif
