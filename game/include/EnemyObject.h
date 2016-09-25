#ifndef ENEMY_OBJECT_LIZARD
#define ENEMY_OBJECT_LIZARD

#include "GameObject.h"
#include "EnemyInputComponent.h"
#include "EnemyGraphicsComponent.h"
#include "EnemyPhysicsComponent.h"

class EnemyInputComponent;
class EnemyGraphicsComponent;
class EnemyPhysicsComponent;

class EnemyObject: public GameObject {
	
	public:
	int x,y, xVelocity, yVelocity;
	SDL_Rect* enemyRect;
	EnemyObject(int x, int y, int xVelocity, int yVelocity, EnemyInputComponent *i, EnemyGraphicsComponent *g,
				 EnemyPhysicsComponent *p);
	~EnemyObject();
	void update(World *world, SDL_Renderer *renderer);
	
	private:
	EnemyInputComponent * input;
	EnemyGraphicsComponent *graphics;
	EnemyPhysicsComponent *physics;
};

#endif
