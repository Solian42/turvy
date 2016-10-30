#ifndef COIN_GRAPHICS_COMPONENT_LIZARD
#define COIN_GRAPHICS_COMPONENT_LIZARD

#include "CoinObject.h"
#include "GraphicsComponent.h"
#include <iostream>
#include <string>
#include <vector>

class CoinObject;

class CoinGraphicsComponent : public GraphicsComponent {
public:
    CoinGraphicsComponent(SDL_Renderer *ren, ResourceManager *r,
                                std::vector<std::string> spritenames);
    void update(World *world);
    ~CoinGraphicsComponent();
    void setCurrState(int state);

private:
    int currState = 0;
    void updateCurrentSprite();
};

#endif