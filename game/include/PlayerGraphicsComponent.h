#ifndef PLAYER_GRAPHICS_COMPONENT_LIZARD
#define PLAYER_GRAPHICS_COMPONENT_LIZARD

#include "GraphicsComponent.h"
#include "PlayerObject.h"
#include <iostream>
#include <string>
#include <vector>
class PlayerObject;
enum {
    RIGHT_GRIN_UP = 0,
    RIGHT_GRIN_DOWN = 1,
    RIGHT_SMILE_UP = 2,
    RIGHT_SMILE_DOWN = 3,
    U_LEFT_GRIN_UP = 4,
    U_LEFT_GRIN_DOWN = 5,
    U_LEFT_SMILE_UP = 6,
    U_LEFT_SMILE_DOWN = 7,
    LEFT_GRIN_UP = 8,
    LEFT_GRIN_DOWN = 9,
    LEFT_SMILE_UP = 10,
    LEFT_SMILE_DOWN = 11,
    U_RIGHT_GRIN_UP = 12,
    U_RIGHT_GRIN_DOWN = 13,
    U_RIGHT_SMILE_UP = 14,
    U_RIGHT_SMILE_DOWN = 15
};
class PlayerGraphicsComponent : public GraphicsComponent {
public:
    PlayerGraphicsComponent(SDL_Renderer *ren, ResourceManager *r,
                            std::vector<std::string> spritenames);
    void update(World *world, int dt);
    ~PlayerGraphicsComponent();
    void setCurrState(int state);
    bool isUpsideDown() { return upsideDown; }

    void setUpsideDown(bool orientation) { upsideDown = orientation; }

private:
    int time = 0;
    int currState = 0;
    bool upsideDown = false;
    void updateCurrentSprite(World *world, int dt);
};

#endif
