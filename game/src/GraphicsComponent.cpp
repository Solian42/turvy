#include "../include/GraphicsComponent.h"

GraphicsComponent::GraphicsComponent(SDL_Renderer *r, ResourceManager * res, std::vector<std::string> spriteNames) {
    myRenderer = r;
    resources = res;
    currentSprite = spriteNames[0];
    this->spriteNames = spriteNames;
    
    SDL_QueryTexture(resources->getTexture(currentSprite), NULL, NULL, &currW, &currH);
}
GraphicsComponent::~GraphicsComponent() {
    
}

void GraphicsComponent::update(SDL_Renderer *renderer, World *world) {
	
    updateCurrentSprite();
	
	SDL_Rect temp = {world->transformX(myObj->getX()), world->transformY(myObj->getY()), currW, currH};
    //SDL_Rect temp = {centerRect(myObj->getX(), currW), centerRect(myObj->getX(), currH), currW, currH};
    
    if (SDL_RenderCopy(renderer, resources->getTexture(currentSprite), NULL, &temp) < 0) {
		std::cout << "Something broke: " << SDL_GetError() << "\n";
	}
	updateParent();
}

void GraphicsComponent::setCurrentSprite(std::string name) {
	currentSprite = name;
}

std::string GraphicsComponent::getCurrentSprite() {
	return currentSprite;
}

SDL_Rect GraphicsComponent::getTextureRect(std::string name) {
    int textureW;
    int textureH;
    SDL_QueryTexture(resources->getTexture(name), NULL, NULL, &textureW, &textureH);
    SDL_Rect temp = {centerRect(myObj->getX(), textureW), centerRect(myObj->getY(), textureH), textureW, textureH};
        return temp;
    
}

int GraphicsComponent::getCurrW() {
    return currW;
}

int GraphicsComponent::getCurrH() {
    return currH;
}

void GraphicsComponent::setGameObject(GameObject *obj) {
    myObj = obj;
}

void GraphicsComponent::updateParent() {
    myObj->setH(currH);
    myObj->setW(currW);
}

