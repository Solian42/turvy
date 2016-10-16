#ifndef PLATFORM_GRAPHICS_COMPONENT_LIZARD
#define PLATFORM_GRAPHICS_COMPONENT_LIZARD

#include "GraphicsComponent.h"
#include "TerrainObject.h"
#include <iostream>
#include <string>
#include <vector>

class TerrainObject;

class TerrainGraphicsComponent : public GraphicsComponent {
public:
	TerrainGraphicsComponent(SDL_Renderer *ren, ResourceManager *r,
                            std::vector<std::string> spritenames);
	void update(World *world, TerrainObject *terrain);
    void setCurrState(int state);

private:
    int currState = 0;
    void updateCurrentSprite(TerrainObject *terrain);
};

#endif