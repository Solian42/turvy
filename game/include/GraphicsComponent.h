#ifndef GRAPHICS_COMPONENT_LIZARD
#define GRAPHICS_COMPONENT_LIZARD

#include "GameObject.h"
#include "ResourceManager.h"
#include "World.h"
#include <SDL.h>
#include <SDL_image.h>
#include <vector>

class GameObject;
class World;
class GraphicsComponent {
public:
    GraphicsComponent(SDL_Renderer *r, ResourceManager *res,
                      std::vector<std::string> spriteNames);
    virtual ~GraphicsComponent();
    void update(World *world, int dt);

    SDL_Rect getTextureRect(std::string name);
    std::string getCurrentSprite();
    int getCurrW();
    int getCurrH();
    int getCurrState();

    void setGameObject(GameObject *obj);
    void setCurrentSprite(std::string name);
    void setCurrentState(int state);
    void scaleCurrentSprite(int scale);
    int centerRect(int large, int small) { return large / 2 - small / 2; }

protected:
    GameObject *myObj;
    ResourceManager *resources;
    int currState = 0;
    void updateParent();
    void updateCurrentSprite();
    std::string currentSprite;
    int currW = 0;
    int currH = 0;
    SDL_Renderer *myRenderer;
    std::vector<std::string> spriteNames;
};

#endif
