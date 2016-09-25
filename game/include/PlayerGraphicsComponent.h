#ifndef PLAYER_GRAPHICS_COMPONENT_LIZARD
#define PLAYER_GRAPHICS_COMPONENT_LIZARD

#include "GraphicsComponent.h"
#include "PlayerObject.h"
#include <string>
#include <iostream>
class PlayerObject;

class PlayerGraphicsComponent : public GraphicsComponent
{
public:
	PlayerGraphicsComponent(std::string textureName,
							SDL_Renderer* renderer);
  	void update(PlayerObject* Playerobj, SDL_Renderer* renderer);
  	~PlayerGraphicsComponent();
  	
  	
  	private:
  	SDL_Texture *playerSprite;
};

void textureSize(SDL_Texture *t, int *w, int *h);


#endif