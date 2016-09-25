#ifndef PLAYER_GRAPHICS_COMPONENT_LIZARD
#define PLAYER_GRAPHICS_COMPONENT_LIZARD

#include "GraphicsComponent.h"
#include <string>
#include <iostream>
class PlayerGraphicsComponent : public GraphicsComponent
{
public:
	PlayerGraphicsComponent(std::string textureName, SDL_Renderer* renderer);
  	void update(GameObject* obj, SDL_Renderer* renderer);
  	~PlayerGraphicsComponent();
  	
  	
  	private:
  	SDL_Texture *playerSprite;
};


#endif