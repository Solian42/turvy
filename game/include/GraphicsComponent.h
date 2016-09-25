#ifndef GRAPHICS_COMPONENT_LIZARD
#define GRAPHICS_COMPONENT_LIZARD

#include "GameObject.h"
#include "World.h"
#include <SDL.h>
#include <SDL_image.h>
class GraphicsComponent
{
public:
  virtual ~GraphicsComponent() {}
  virtual void update(GameObject& obj, SDL_Renderer& renderer) = 0;
};

#endif
