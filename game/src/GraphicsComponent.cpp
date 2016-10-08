#include "../include/GraphicsComponent.h"

GraphicsComponent::GraphicsComponent(SDL_Renderer *r, ResourceManager *res,
                                     std::vector<std::string> spriteNames) {
    myRenderer = r;
    resources = res;
    currentSprite = spriteNames[0];
    this->spriteNames = spriteNames;

    SDL_QueryTexture(resources->getTexture(currentSprite), NULL, NULL, &currW,
                     &currH);
}
GraphicsComponent::~GraphicsComponent() {}

void GraphicsComponent::update(World *world, int dt) {

    updateCurrentSprite();

    SDL_Rect temp = {world->transformX(myObj->getX()),
                     world->transformY(myObj->getY()), currW, currH};
    // SDL_Rect temp = {centerRect(myObj->getX(), currW),
    // centerRect(myObj->getX(), currH), currW, currH};

    if (SDL_RenderCopy(myRenderer, resources->getTexture(currentSprite), NULL,
                       &temp) < 0) {
        std::cout << "Something broke: " << SDL_GetError() << "\n";
    }
    updateParent();

    int supressWarnings = dt;
    supressWarnings++;
}

void GraphicsComponent::setCurrentSprite(std::string name) {
    currentSprite = name;
}

void GraphicsComponent::setCurrentState(int state) { currState = state; }

void GraphicsComponent::updateCurrentSprite() {
    currentSprite = spriteNames[currState];
}

std::string GraphicsComponent::getCurrentSprite() { return currentSprite; }

SDL_Rect GraphicsComponent::getTextureRect(std::string name) {
    int textureW;
    int textureH;
    SDL_QueryTexture(resources->getTexture(name), NULL, NULL, &textureW,
                     &textureH);
    SDL_Rect temp = {centerRect(myObj->getX(), textureW),
                     centerRect(myObj->getY(), textureH), textureW, textureH};
    return temp;
}

int GraphicsComponent::getCurrW() { return currW; }

int GraphicsComponent::getCurrH() { return currH; }

int GraphicsComponent::getCurrState() { return currState; }
void GraphicsComponent::setGameObject(GameObject *obj) { myObj = obj; }

void GraphicsComponent::updateParent() {
    myObj->setH(currH);
    myObj->setW(currW);
}

void GraphicsComponent::scaleCurrentSprite(int scale) {
    SDL_QueryTexture(resources->getTexture(currentSprite), NULL, NULL, &currW,
                     &currH);
    currW *= scale;
    currH *= scale;
}
