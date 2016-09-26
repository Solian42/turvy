#include "../include/EnemyGraphicsComponent.h"

int centerEnemy(int large, int small) { return large / 2 - small / 2; }

EnemyGraphicsComponent::EnemyGraphicsComponent(std::string textureName,
                                               SDL_Renderer *renderer) {
    SDL_Surface *image = IMG_Load(textureName.c_str());
    if (!image) {
        std::cout << "IMG_Load: " << IMG_GetError() << "\n";
    }
    this->enemySprite = SDL_CreateTextureFromSurface(renderer, image);
    if (this->enemySprite == NULL) {
        std::cout << "Something broke: " << SDL_GetError();
    }
    SDL_FreeSurface(image);
    SDL_QueryTexture(this->enemySprite, NULL, NULL, &textureW, &textureH);
}

EnemyGraphicsComponent::~EnemyGraphicsComponent() {}

void EnemyGraphicsComponent::update(EnemyObject *enemyObj,
                                    SDL_Renderer *renderer, World *world) {

    SDL_Rect destination = {world->transformX(enemyObj->x),
                            world->transformY(enemyObj->y), textureW, textureH};
    if (SDL_RenderCopy(renderer, this->enemySprite, NULL, &destination) < 0) {
        std::cout << "Something broke: " << SDL_GetError() << "\n";
    }
}

int EnemyGraphicsComponent::getTextureW() { return textureW; }
int EnemyGraphicsComponent::getTextureH() { return textureH; }
