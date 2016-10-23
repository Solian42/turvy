#ifndef CHECKPOINT_GRAPHICS_COMPONENT_LIZARD
#define CHECKPOINT_GRAPHICS_COMPONENT_LIZARD

#include "GraphicsComponent.h"
#include "CheckpointObject.h"
#include <iostream>
#include <string>
#include <vector>

class CheckpointObject;

class CheckpointGraphicsComponent : public GraphicsComponent {
public:
	CheckpointGraphicsComponent(SDL_Renderer *ren, ResourceManager *r,
		                        std::vector<std::string> spritenames);
	void update(World *world);
    ~CheckpointGraphicsComponent();
    void setCurrState(int state);

private:
	int currState = 0;
	void updateCurrentSprite();
};

#endif