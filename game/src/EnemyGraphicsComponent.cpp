#include "../include/EnemyGraphicsComponent.h"

EnemyGraphicsComponent::EnemyGraphicsComponent(std::string textureName, SDL_Renderer *
                                                 renderer) {
    SDL_Surface *image =
        IMG_Load(textureName.c_str());
    if (!image) {
        std::cout << "IMG_Load: " << IMG_GetError() << "\n";
    }
    this->enemySprite = SDL_CreateTextureFromSurface(renderer, image); 
    if (this->enemySprite == NULL) {
        std::cout << "Something broke: " << SDL_GetError();
    }
    SDL_FreeSurface(image);
    
    
    
}

EnemyGraphicsComponent::~EnemyGraphicsComponent() {}

void EnemyGraphicsComponent::update(EnemyObject* enemyObj, SDL_Renderer* renderer) {
    
    if(enemyObj->enemyRect->w == 0) {
        int textureW, textureH;
        SDL_QueryTexture(this->enemySprite, NULL, NULL, &textureW, &textureH);
        enemyObj->enemyRect->w = textureW;
        enemyObj->enemyRect->w = textureH;
    }
    
    if (SDL_RenderCopy(renderer, this->enemySprite, NULL, enemyObj->enemyRect) < 0) {
            std::cout << "Something broke: " << SDL_GetError();
        }
}
