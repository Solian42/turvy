#ifndef TELEPORT_GRAPHICS_COMPONENT_LIZARD
#define TELEPORT_GRAPHICS_COMPONENT_LIZARD

#include "TeleportObject.h"
#include "GraphicsComponent.h"
#include <iostream>
#include <string>
#include <vector>

class TeleportObject;

class TeleportGraphicsComponent : public GraphicsComponent {
public:
    TeleportGraphicsComponent(SDL_Renderer *ren, ResourceManager *r,
                                std::vector<std::string> spritenames);
    void update(World *world, int dt);
    ~TeleportGraphicsComponent();
    void setCurrState(int state);

private:
    int time = 0;
    int currState = 0;
    void updateCurrentSprite(int dt);
};

#endif
