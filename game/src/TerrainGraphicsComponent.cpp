#include "../include/TerrainGraphicsComponent.h"
TerrainGraphicsComponent::TerrainGraphicsComponent(
    SDL_Renderer *ren, ResourceManager *r, std::vector<std::string> spritenames)
    : GraphicsComponent(ren, r, spritenames) {}

void TerrainGraphicsComponent::update(World *world, TerrainObject *terrain) {

	updateCurrentSprite(terrain);

    SDL_Rect temp = {world->transformX(myObj->getX()),
                     world->transformY(myObj->getY()), currW, currH};
    // SDL_Rect temp = {centerRect(myObj->getX(), currW),
    // centerRect(myObj->getX(), currH), currW, currH};

    if (SDL_RenderCopy(myRenderer, resources->getTexture(currentSprite), NULL,
                       &temp) < 0) {
        std::cout << "Something broke: " << SDL_GetError() << " "
                  << currentSprite << "\n";
    }
    /* Code to test Collisions. Turns things into rectangles.
    SDL_SetRenderDrawColor(myRenderer, 255, 0, 0, 255);
    SDL_RenderFillRect(myRenderer, &temp);
    SDL_SetRenderDrawColor(myRenderer, 0, 0, 0, 255);*/
    //updateParent();
}

void TerrainGraphicsComponent::updateCurrentSprite(TerrainObject *terrain) {

    /* Sets the sprite based of if its a spike, and if so if its upside down. */
	if (terrain->isSpikes()) { 
        if (terrain->isUpsideDown()) {
            currState = 2;
        } else {
            currState = 1;
        }

    } else {
        currState = 0;
    }

	currentSprite = spriteNames[currState];

}

void TerrainGraphicsComponent::setCurrState(int state) {
    currState = state;
    currentSprite = spriteNames[currState];
}