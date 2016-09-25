#ifndef ENEMY_OBJECT_LIZARD
#define ENEMY_OBJECT_LIZARD

#include "GameObject.h"
#include "InputComponent.h"
#include "GraphicsComponent.h"
#include "PhysicsComponent.h"
class EnemyObject: public GameObject {
	
	public:
	int x,y,velocity;
	EnemyObject(int x, int y, int velocity, InputComponent *i, GraphicsComponent *g,
				 PhysicsComponent *p);
	void update();
	
	private:
	InputComponent * input;
	GraphicsComponent *graphics;
	PhysicsComponent *physics;
};

#endif
