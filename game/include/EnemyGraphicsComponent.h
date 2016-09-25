#ifndef ENEMY_GRAPHICS_COMPONENT_LIZARD
#define ENEMY_GRAPHICS_COMPONENT_LIZARD

#include "GraphicsComponent.h"
#include "EnemyObject.h"
#include <string>
#include <iostream>
class EnemyObject;

class EnemyGraphicsComponent : public GraphicsComponent
{
public:
	EnemyGraphicsComponent(std::string textureName, SDL_Renderer* renderer);
  	void update(EnemyObject* enemyObj, SDL_Renderer* renderer);
  	~EnemyGraphicsComponent();
  	
  	
  	private:
  	SDL_Texture *enemySprite;
};

#endif