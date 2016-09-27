#ifndef ENEMY_GRAPHICS_COMPONENT_LIZARD
#define ENEMY_GRAPHICS_COMPONENT_LIZARD

#include "EnemyObject.h"
#include "GraphicsComponent.h"
#include <iostream>
#include <string>
class EnemyObject;

class EnemyGraphicsComponent : public GraphicsComponent {
public:
    EnemyGraphicsComponent(std::string textureName, SDL_Renderer *renderer);
    void update(EnemyObject *enemyObj, SDL_Renderer *renderer, World *world);
    ~EnemyGraphicsComponent();

    int getTextureW();
    int getTextureH();

private:
    SDL_Texture *enemySprite;
    int textureW;
    int textureH;
};

#endif
