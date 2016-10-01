#ifndef GRAPHICS_COMPONENT_LIZARD
#define GRAPHICS_COMPONENT_LIZARD

#include "GameObject.h"
#include "ResourceManager.h"
#include "World.h"
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
class GraphicsComponent {
public:
    GraphicsComponent(SDL_Renderer *r, ResourceManager *res,
                      std::vector<std::string> spriteNames);
    virtual ~GraphicsComponent();
    void update(SDL_Renderer *renderer, World *world);

    SDL_Rect getTextureRect(std::string name);
    std::string getCurrentSprite();
    int getCurrW();
    int getCurrH();

    void setGameObject(GameObject *obj);
    void setCurrentSprite(std::string name);

    int centerRect(int large, int small) { return large / 2 - small / 2; }

protected:
    GameObject *myObj;
    ResourceManager *resources;
    void updateParent();
    virtual void updateCurrentSprite() = 0;
    std::string currentSprite;
    int currW = 0;
    int currH = 0;
    SDL_Renderer *myRenderer;
    std::vector<std::string> spriteNames;
};

#endif
