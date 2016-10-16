#ifndef PLATFORM_GRAPHICS_COMPONENT_LIZARD
#define PLATFORM_GRAPHICS_COMPONENT_LIZARD

#include "GraphicsComponent.h"
#include "PlatformObject.h"
#include <iostream>
#include <string>
#include <vector>

class PlatformObject;

class PlatformGraphicsComponent : public GraphicsComponent {
public:
	PlatformGraphicsComponent(SDL_Renderer *ren, ResourceManager *r,
                            std::vector<std::string> spritenames);
	void update(World *world);
	~PlatformGraphicsComponent();
    void setCurrState(int state);

private:
    int currState = 0;
    void updateCurrentSprite();
};

#endif