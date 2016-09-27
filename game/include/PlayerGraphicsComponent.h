#ifndef PLAYER_GRAPHICS_COMPONENT_LIZARD
#define PLAYER_GRAPHICS_COMPONENT_LIZARD

#include "GraphicsComponent.h"
#include "PlayerObject.h"
#include <iostream>
#include <string>
class PlayerObject;

class PlayerGraphicsComponent : public GraphicsComponent {
public:
    PlayerGraphicsComponent(std::string textureName, SDL_Renderer *renderer);
    void update(PlayerObject *Playerobj, SDL_Renderer *renderer, World *world);
    ~PlayerGraphicsComponent();

    int getTextureW();
    int getTextureH();

private:
    SDL_Texture *playerSprite;
    int textureW;
    int textureH;
};

#endif
