#ifndef TRAMPOLINE_GRAPHICS_COMPONENT_LIZARD
#define TRAMPOLINE_GRAPHICS_COMPONENT_LIZARD

#include "GraphicsComponent.h"
#include "TrampolineObject.h"
#include <iostream>
#include <string>
#include <vector>

class TrampolineObject;

class TrampolineGraphicsComponent : public GraphicsComponent {
public:
    TrampolineGraphicsComponent(SDL_Renderer *ren, ResourceManager *r,
                                std::vector<std::string> spritenames);
    void update(World *world);
    ~TrampolineGraphicsComponent();
    void setCurrState(int state);

private:
    int currState = 0;
    void updateCurrentSprite();
};

#endif
