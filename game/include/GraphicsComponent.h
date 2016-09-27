#ifndef GRAPHICS_COMPONENT_LIZARD
#define GRAPHICS_COMPONENT_LIZARD

#include "GameObject.h"
#include "World.h"
#include <SDL.h>
#include <SDL_image.h>
class GraphicsComponent {
public:
    virtual ~GraphicsComponent() {}
    void update(GameObject *obj, SDL_Renderer *renderer);

private:
    SDL_Renderer *renderer;
};

#endif
