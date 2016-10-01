#include "../include/EnemyGraphicsComponent.h"

int centerEnemy(int large, int small) { return large / 2 - small / 2; }

EnemyGraphicsComponent::EnemyGraphicsComponent(
    SDL_Renderer *ren, ResourceManager *r, std::vector<std::string> spritenames)
    : GraphicsComponent(ren, r, spritenames) {}

EnemyGraphicsComponent::~EnemyGraphicsComponent() {}

void EnemyGraphicsComponent::updateCurrentSprite() {
    // Logic goes here. Kappa.
    currentSprite = spriteNames[0];
}
