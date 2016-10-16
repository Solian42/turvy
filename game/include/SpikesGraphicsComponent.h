#ifndef SPIKES_GRAPHICS_COMPONENT_LIZARD
#define SPIKES_GRAPHICS_COMPONENT_LIZARD

#include "GraphicsComponent.h"
#include "SpikesObject.h"
#include <iostream>
#include <string>
#include <vector>

class SpikesObject;

class SpikesGraphicsComponent : public GraphicsComponent {
public:
    SpikesGraphicsComponent(SDL_Renderer *ren, ResourceManager *r,
                            std::vector<std::string> spritenames);
    void update(World *world, SpikesObject *spikes);
    ~SpikesGraphicsComponent();
    void setCurrState(int state);

private:
    int currState = 0;
    void updateCurrentSprite(SpikesObject *spikes);
};

#endif