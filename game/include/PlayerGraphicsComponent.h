#ifndef PLAYER_GRAPHICS_COMPONENT_LIZARD
#define PLAYER_GRAPHICS_COMPONENT_LIZARD

#include "GraphicsComponent.h"
#include "PlayerObject.h"
#include <iostream>
#include <string>
#include <vector>
class PlayerObject;

class PlayerGraphicsComponent : public GraphicsComponent {
public:
    PlayerGraphicsComponent(SDL_Renderer *ren, ResourceManager *r,
                            std::vector<std::string> spritenames);
    void update(SDL_Renderer *renderer, World *world, int dt);
    ~PlayerGraphicsComponent();
    void setCurrState(int state);

private:
    int time = 0;
    int currState = 0;
    bool upsideDown = false;
    void updateCurrentSprite(int dt);
};

#endif
