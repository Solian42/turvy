#ifndef ENEMY_GRAPHICS_COMPONENT_LIZARD
#define ENEMY_GRAPHICS_COMPONENT_LIZARD

#include "EnemyObject.h"
#include "GraphicsComponent.h"
#include <iostream>
#include <string>
class EnemyObject;

class EnemyGraphicsComponent : public GraphicsComponent {
public:
    EnemyGraphicsComponent(SDL_Renderer *ren, ResourceManager *r,
                           std::vector<std::string> spritenames);
    void update(SDL_Renderer *renderer, World *world, int dt);
    ~EnemyGraphicsComponent();

private:
    int time = 0;
    int currState = 0;
    void updateCurrentSprite(int dt);
};

#endif
