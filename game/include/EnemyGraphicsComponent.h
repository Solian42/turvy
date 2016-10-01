#ifndef ENEMY_GRAPHICS_COMPONENT_LIZARD
#define ENEMY_GRAPHICS_COMPONENT_LIZARD

#include "EnemyObject.h"
#include "GraphicsComponent.h"
#include <iostream>
#include <string>
class EnemyObject;

class EnemyGraphicsComponent : public GraphicsComponent {
public:
    EnemyGraphicsComponent(SDL_Renderer * ren, ResourceManager *r, std::vector<std::string> spritenames);
    void update(EnemyObject *enemyObj, SDL_Renderer *renderer, World *world);
    ~EnemyGraphicsComponent();


private:
    void updateCurrentSprite();
};

#endif
