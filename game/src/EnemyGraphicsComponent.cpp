#include "../include/EnemyGraphicsComponent.h"

int centerEnemy(int large, int small) { return large / 2 - small / 2; }

EnemyGraphicsComponent::EnemyGraphicsComponent(
    SDL_Renderer *ren, ResourceManager *r, std::vector<std::string> spritenames)
    : GraphicsComponent(ren, r, spritenames) {}

EnemyGraphicsComponent::~EnemyGraphicsComponent() {}

void EnemyGraphicsComponent::update(SDL_Renderer *renderer, World *world, int dt) {
    
    updateCurrentSprite(dt);
    
    SDL_Rect temp = {world->transformX(myObj->getX()),
        world->transformY(myObj->getY()), currW, currH};
    // SDL_Rect temp = {centerRect(myObj->getX(), currW),
    // centerRect(myObj->getX(), currH), currW, currH};
    
    if (SDL_RenderCopy(renderer, resources->getTexture(currentSprite), NULL,
                       &temp) < 0) {
        std::cout << "Something broke: " << SDL_GetError() << "\n";
    }
    updateParent();
}

void EnemyGraphicsComponent::updateCurrentSprite(int dt) {
    if(myObj->getXVel() != 0.0 || myObj->getYVel() != 0.0) {
        time += dt;
        if (time > 200) {
            time -= 200;
            switch (currState) {
                case 0:
                    currState = 1;
                    break;
                case 1:
                    currState = 2;
                    break;

                case 2:
                    currState = 3;
                    break;

                case 3:
                    currState = 4;
                    break;
                case 4:
                    
                    currState = 5;
                    break;
                case 5:
                    
                    currState = 0;
                    break;
                default:
                    break;
            }
        }
        currentSprite = spriteNames[currState];
    }
}
